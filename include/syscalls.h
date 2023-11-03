 #ifndef __HOBBYOS__SYSCALLS_H
#define __HOBBYOS__SYSCALLS_H

#include <common/types.h>
#include <hardware/interrupts.h>
#include <multitasking.h>

namespace hobbyos
{
    
    class SyscallHandler : public hardware::InterruptHandler
    {
        
    public:
        SyscallHandler(hardware::InterruptManager* interruptManager, hobbyos::common::uint8_t InterruptNumber);
        ~SyscallHandler();
        
        virtual hobbyos::common::uint32_t HandleInterrupt(hobbyos::common::uint32_t esp);

    };
    
    
}


#endif