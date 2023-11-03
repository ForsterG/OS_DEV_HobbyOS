.code32
.set IRQ_BASE, 0x20

.section .text

.extern _ZN7hobbyos8hardware16InterruptManager15HandleInterruptEhj


.macro HandleException num
.global _ZN7hobbyos8hardware16InterruptManager19HandleException\num\()Ev
_ZN7hobbyos8hardware16InterruptManager19HandleException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom_no_error
.endm

.macro HandleExceptionWithError num
.global _ZN7hobbyos8hardware16InterruptManager19HandleException\num\()Ev
_ZN7hobbyos8hardware16InterruptManager19HandleException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom_error
.endm


.macro HandleInterruptRequest num
.global _ZN7hobbyos8hardware16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN7hobbyos8hardware16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom_no_error
.endm

HandleException 0x00
HandleException 0x01
HandleException 0x02
HandleException 0x03
HandleException 0x04
HandleException 0x05
HandleException 0x06
HandleException 0x07
HandleExceptionWithError 0x08
HandleException 0x09
HandleExceptionWithError 0x0A
HandleExceptionWithError 0x0B
HandleExceptionWithError 0x0C
HandleExceptionWithError 0x0D
HandleExceptionWithError 0x0E
HandleException 0x0F
HandleException 0x10
HandleExceptionWithError 0x11
HandleException 0x12
HandleException 0x13
HandleException 0x14
HandleExceptionWithError 0x15
HandleException 0x16
HandleException 0x17
HandleException 0x18
HandleException 0x19
HandleException 0x1A
HandleException 0x1B
HandleException 0x1C
HandleExceptionWithError 0x1D
HandleExceptionWithError 0x1E
HandleException 0x1F

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

HandleInterruptRequest 0x80


int_bottom_error:
    cli

    pushl %ebp
    pushl %edi
    pushl %esi
    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax

    pushl %esp
    push (interruptnumber)
    jmp .
    call _ZN7hobbyos8hardware16InterruptManager15HandleInterruptEhj

    addl $0x4, %esp #remove error code
    addl $0x8, %esp #cleanup stack

    popl %eax
    popl %ebx
    popl %ecx
    popl %edx
    popl %esi
    popl %edi
    popl %ebp

    
    
    sti
    iretl

int_bottom_no_error:
    cli

    pushl %ebp
    pushl %edi
    pushl %esi
    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax

    pushl %esp
    pushl (interruptnumber)
    call _ZN7hobbyos8hardware16InterruptManager15HandleInterruptEhj

    addl $0x8, %esp #cleanup stack
    
    popl %eax
    popl %ebx
    popl %ecx
    popl %edx
    popl %esi
    popl %edi
    popl %ebp
    
    sti
    iretl

    # load ring 0 segment register
    #cld
    #mov $0x10, %eax
    #mov %eax, %eds
    #mov %eax, %ees

    # call C++ Handler
    ##pushl %esp
    ##push (interruptnumber)
    #call _ZN7hobbyos8hardware16InterruptManager15HandleInterruptEhj
    #add %esp, 6
    ##mov %eax, %esp # switch the stack

#.global _ZN7hobbyos8hardware16InterruptManager15InterruptIgnoreEv
#_ZN7hobbyos8hardware16InterruptManager15InterruptIgnoreEv:

    #iret


.data
    interruptnumber: .byte 0
