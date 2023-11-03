.code32

#FIXME:assumes GDT Kernel code SD is 0x08 and data is 0x10
#should fix in future
.global ASM_LGDT_ReloadSegReg
ASM_LGDT_ReloadSegReg:
    movl 4(%esp), %eax
    inc %eax
    inc %eax#needed to move from 8 byte struct to six byte
    cli
    lgdt (%EAX)
    movl $0x10, %EDX
    movl %EDX, %DS
    jmpl $0x08,$_reload_cs 
_reload_cs:
    cli
    movw $0x10, %AX
    movw %AX, %DS
    movw %AX, %ES
    movw %AX, %FS
    movw %AX, %GS
    movw %AX, %SS
    ret
