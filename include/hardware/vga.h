#ifndef __HOBBYOS__HARDWARECOMMUNICATION__VGA_H
#define __HOBBYOS__HARDWARECOMMUNICATION__VGA_H

#include <common/types.h>

namespace hobbyos
{
    namespace hardware
    {
        class VGA
        {

            public:
                static void set_cursor(hobbyos::common::uint8_t x, hobbyos::common::uint8_t y);
                static void print_char(hobbyos::common::uint8_t character);
                static void printf(hobbyos::common::string);
                static void printfHex8(hobbyos::common::uint8_t);
                static void printfHex16(hobbyos::common::uint16_t);
                static void printfHex32(hobbyos::common::uint32_t);
                static void printfHex64(hobbyos::common::uint64_t);

                static void printfMem8(hobbyos::common::uint8_t*);
                static void printfMem16(hobbyos::common::uint8_t*);
                static void printfMem32(hobbyos::common::uint8_t*);
                static void printfMem64(hobbyos::common::uint8_t*);

                static hobbyos::common::uint8_t GetCursor_x();
                static hobbyos::common::uint8_t GetCursor_y();

                static void clear_screen();
            private:
                static hobbyos::common::uint8_t cursor_x;
                static hobbyos::common::uint8_t cursor_y;
                static const hobbyos::common::uint8_t cursor_x_max = 80;
                static const hobbyos::common::uint8_t cursor_y_max = 25;
                static const hobbyos::common::size_t buffer_address = 0xB8000;

        };
    }
}

#endif