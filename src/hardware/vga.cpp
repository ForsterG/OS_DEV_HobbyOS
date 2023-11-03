#include <hardware/vga.h>

using namespace hobbyos::common;
using namespace hobbyos::hardware;

uint8_t VGA::cursor_x = 0;
uint8_t VGA::cursor_y = 0;


void hobbyos::hardware::VGA::set_cursor(uint8_t x, uint8_t y)
{
    cursor_x = x;
    cursor_y = y;

    if(cursor_x >= cursor_x_max)
    {
        cursor_x = 0;
        cursor_y += 1;
    }
    if(cursor_y >= cursor_y_max)
    {
        cursor_y = 0;
    }
}

uint8_t VGA::GetCursor_x()
{
    return cursor_x;
}
uint8_t VGA::GetCursor_y()
{
    return cursor_y;
}

void hobbyos::hardware::VGA::print_char(uint8_t character)
{
    uint16_t * location = (uint16_t*)buffer_address + cursor_x + (cursor_y * cursor_x_max); 
    uint8_t color = 0x0F;//white on black
    uint16_t entry = (((uint16_t)color)<<8) | (uint16_t) character;
    *location = (uint16_t)entry;

    cursor_x += 1;
    if(cursor_x >= cursor_x_max)
    {
        cursor_x = 0;
        cursor_y += 1;
    }
    if(cursor_y >= cursor_y_max)
    {
        cursor_y = 0;
    }
}

void hobbyos::hardware::VGA::printf(string str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        switch (str[i])
        {
        case '\n':
            VGA::set_cursor(0, cursor_y + 1);
            break;
        
        default:
            VGA::print_char(str[i]);
            break;
        }
    }
}

void hobbyos::hardware::VGA::clear_screen()
{
    set_cursor(0,0);
    for(int x =0; x < 80*25;x++)
    {
        printf(" ");
    }
    set_cursor(0,0);
}

void hobbyos::hardware::VGA::printfMem8(uint8_t* mem)
{
    uint8_t mem_byte = (uint8_t)*mem;
    printfHex8(mem_byte);
}
void hobbyos::hardware::VGA::printfMem16(uint8_t* mem)
{
    uint8_t mem_byte = (uint8_t)*(mem+1);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem);
    printfHex8(mem_byte);
}
void hobbyos::hardware::VGA::printfMem32(uint8_t* mem)
{
    uint8_t mem_byte = (uint8_t)*(mem+3);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+2);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+1);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem);
    printfHex8(mem_byte);
}
void hobbyos::hardware::VGA::printfMem64(uint8_t* mem)
{
    uint8_t mem_byte = (uint8_t)*(mem+7);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+6);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+5);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+4);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+3);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+2);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem+1);
    printfHex8(mem_byte);
    mem_byte = (uint8_t)*(mem);
    printfHex8(mem_byte);
}

void hobbyos::hardware::VGA::printfHex8(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    VGA::printf(foo);
}
void hobbyos::hardware::VGA::printfHex16(uint16_t key)
{
    VGA::printfHex8((key >> 8) & 0xFF);
    VGA::printfHex8( key & 0xFF);
}
void hobbyos::hardware::VGA::printfHex32(uint32_t key)
{
    VGA::printfHex8((key >> 24) & 0xFF);
    VGA::printfHex8((key >> 16) & 0xFF);
    VGA::printfHex8((key >> 8) & 0xFF);
    VGA::printfHex8( key & 0xFF);
}
void hobbyos::hardware::VGA::printfHex64(uint64_t key)
{
    VGA::printfHex8((key >> 56) & 0xFF);
    VGA::printfHex8((key >> 48) & 0xFF);
    VGA::printfHex8((key >> 40) & 0xFF);
    VGA::printfHex8((key >> 32) & 0xFF);
    VGA::printfHex8((key >> 24) & 0xFF);
    VGA::printfHex8((key >> 16) & 0xFF);
    VGA::printfHex8((key >> 8) & 0xFF);
    VGA::printfHex8( key & 0xFF);
}











