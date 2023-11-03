
#include <syscalls.h>
#include <hardware/vga.h>
 
using namespace hobbyos;
using namespace hobbyos::common;
using namespace hobbyos::hardware;
 
SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
:    InterruptHandler(interruptManager, InterruptNumber  + interruptManager->GetHardwareInterruptOffset())
{
}

SyscallHandler::~SyscallHandler()
{
}

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;
    

    switch(cpu->eax)
    {
        case 4:
            VGA::printf((char*)cpu->ebx);
            break;
            
        default:
            break;
    }

    
    return esp;
}

