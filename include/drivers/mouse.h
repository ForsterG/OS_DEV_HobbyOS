#ifndef __HOBBYOS__DRIVERS__MOUSE_H
#define __HOBBYOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardware/port.h>
#include <drivers/driver.h>
#include <hardware/interrupts.h>

namespace hobbyos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(hobbyos::common::uint8_t button);
            virtual void OnMouseUp(hobbyos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public hobbyos::hardware::InterruptHandler, public Driver
        {
            hobbyos::hardware::Port8Bit dataport;
            hobbyos::hardware::Port8Bit commandport;
            hobbyos::common::uint8_t buffer[3];
            hobbyos::common::uint8_t offset;
            hobbyos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(hobbyos::hardware::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual hobbyos::common::uint32_t HandleInterrupt(hobbyos::common::uint32_t esp);
            virtual void Activate();
        };


        
        class MouseToConsole : public MouseEventHandler
        {
            common::int8_t x, y;
            public:
    
            MouseToConsole();
            virtual void OnMouseMove(int xoffset, int yoffset);
        };

    }
}
    
#endif
