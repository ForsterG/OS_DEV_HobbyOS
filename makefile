# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso
# unset GTK_PATH, some visual studio code, pthread???? command line varible that interferes with qemu launch
# for virtual box instead of qemu for the run command
# 	(killall VirtualBox && sleep 1) || true
#	VirtualBox --startvm 'hobby Operating System' &

GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin \
		    -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings \
			-nostartfiles -fno-omit-frame-pointer -nodefaultlibs

ASPARAMS = --32

LDPARAMS = -melf_i386

objects = obj/loader.o \
		  obj/kernel.o \
		  obj/hardware/vga.o \
		  obj/gdt.o \
		  obj/gdt_asm.o \
		  obj/hardware/port.o \
		  obj/hardware/interrupts.o \
		  obj/hardware/interruptstubs.o \
		  obj/drivers/driver.o \
		  obj/drivers/keyboard.o \
		  obj/drivers/mouse.o
#		  obj/multitasking.o 
#		  obj/memorymanagement.o \
#         obj/syscalls.o \
          


obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

hobbykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

hobbykernel.iso: hobbykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp hobbykernel.bin iso/boot/hobbykernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Hobby Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/hobbykernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=hobbykernel.iso iso
	rm -rf iso

install: hobbykernel.bin
	sudo cp $< /boot/hobbykernel.bin

.PHONY: run
run: hobbykernel.iso
	unset GTK_PATH
	qemu-system-i386 -hda $< -monitor stdio -d int

.PHONY: clean
clean:
	rm -rf obj hobbykernel.bin hobbykernel.iso
