#ifndef __HOBBYOS__DRIVERS__KEYBOARD_H
#define __HOBBYOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <hardware/port.h>

namespace hobbyos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public hobbyos::hardware::InterruptHandler, public Driver
        {
            hobbyos::hardware::Port8Bit dataport;
            hobbyos::hardware::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(hobbyos::hardware::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual hobbyos::common::uint32_t HandleInterrupt(hobbyos::common::uint32_t esp);
            virtual void Activate();
        };

        class PrintfKeyboardEventHandler : public KeyboardEventHandler
        {
        public:
            PrintfKeyboardEventHandler();
            void OnKeyDown(char);
            void OnKeyUp(char);

        };

    }
}
    
#endif