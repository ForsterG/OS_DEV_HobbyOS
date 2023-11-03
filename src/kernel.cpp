#include <common/types.h>
#include <hardware/vga.h>
#include <gdt.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
//#include <multitasking.h>
//#include <memorymanagement.h>
//#include <syscalls.h>

using namespace hobbyos;
using namespace hobbyos::common;
using namespace hobbyos::hardware;
using namespace hobbyos::drivers;

/*
void sysprintf(char* str)
{
    asm("int $0x80" : : "a" (4), "b" (str));
}

void taskA()
{
    while(true)
        sysprintf("A");
}

void taskB()
{
    while(true)
        sysprintf("B");
}
*/

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(const void* multiboot_structure, uint32_t multiboot_magic_number)
{
    VGA::clear_screen();

    VGA::printf("Initialize GDT\n");
    hobbyos::GlobalDescriptorTable gdt;
    gdt.LoadLGDTRegister();
    //VGA::printfHex32(gdt.GetCodeSegmentSelector());
    VGA::printf("GDT Loading Complete\n");

    VGA::printf("Initialize IDT\n");
    InterruptManager IDT(0x20, &gdt);
    IDT.Activate();
    VGA::printf("IDT Activation Complete\n");


    DriverManager driverManager;

    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&IDT, &kbhandler);
    driverManager.AddDriver(&keyboard);

    MouseToConsole mousehandler;
    MouseDriver mouse(&IDT, &mousehandler);
    driverManager.AddDriver(&mouse);

    driverManager.ActivateAll();

    /*uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure) + 8);
    size_t heap = 10*1024*1024;
    MemoryManager memoryManager(heap, (*memupper)*1024 - heap - 10*1024);
    
    printf("heap: 0x");
    printfHex8((heap >> 24) & 0xFF);
    printfHex8((heap >> 16) & 0xFF);
    printfHex8((heap >> 8 ) & 0xFF);
    printfHex8((heap      ) & 0xFF);
    
    void* allocated = memoryManager.malloc(1024);
    printf("\nallocated: 0x");
    printfHex8(((size_t)allocated >> 24) & 0xFF);
    printfHex8(((size_t)allocated >> 16) & 0xFF);
    printfHex8(((size_t)allocated >> 8 ) & 0xFF);
    printfHex8(((size_t)allocated      ) & 0xFF);
    printf("\n");
    */
    /*
    
    /TaskManager taskManager;
    Task task1(&gdt, taskA);
    Task task2(&gdt, taskB);
    taskManager.AddTask(&task1);
    taskManager.AddTask(&task2);
    
    
    
    SyscallHandler syscalls(&interrupts, 0x80);
    */

    while(1)
    {

    }
}
