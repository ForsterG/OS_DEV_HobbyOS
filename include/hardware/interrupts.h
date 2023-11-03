
#ifndef __HOBBYOS__HARDWARE__INTERRUPTMANAGER_H
#define __HOBBYOS__HARDWARE__INTERRUPTMANAGER_H

#include <gdt.h>
//#include <multitasking.h>
#include <common/types.h>
#include <hardware/port.h>


namespace hobbyos
{
    namespace hardware
    {

        class InterruptManager;

        class InterruptHandler
        {
            friend class InterruptManager;
        protected:
            hobbyos::common::uint8_t InterruptNumber;
            InterruptManager* interruptManager;
            InterruptHandler(InterruptManager* interruptManager, hobbyos::common::uint8_t InterruptNumber);
            ~InterruptHandler();
        public:
            virtual hobbyos::common::uint32_t HandleInterrupt(hobbyos::common::uint32_t esp);
        };


        class InterruptManager
        {
            friend class InterruptHandler;
            protected:

                static InterruptManager* ActiveInterruptManager;
                InterruptHandler* FunctionHandlers[256];
                //TaskManager *taskManager;

                struct GateDescriptor
                {
                    hobbyos::common::uint16_t handlerAddressLowBits;
                    hobbyos::common::uint16_t gdt_codeSegmentSelector;
                    hobbyos::common::uint8_t reserved;
                    hobbyos::common::uint8_t access;
                    hobbyos::common::uint16_t handlerAddressHighBits;
                } __attribute__((packed));

                static GateDescriptor interruptDescriptorTable[256];

                struct InterruptDescriptorTablePointer
                {
                    hobbyos::common::uint16_t size;
                    hobbyos::common::uint32_t base;
                } __attribute__((packed));

                hobbyos::common::uint16_t hardwareInterruptOffset;
                static void SetIDTEntry(hobbyos::common::uint8_t interrupt,
                    hobbyos::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),
                    hobbyos::common::uint8_t DescriptorPrivilegeLevel, hobbyos::common::uint8_t DescriptorType);


                //static void InterruptIgnore();

                static void HandleInterruptRequest0x00();
                static void HandleInterruptRequest0x01();
                static void HandleInterruptRequest0x02();
                static void HandleInterruptRequest0x03();
                static void HandleInterruptRequest0x04();
                static void HandleInterruptRequest0x05();
                static void HandleInterruptRequest0x06();
                static void HandleInterruptRequest0x07();
                static void HandleInterruptRequest0x08();
                static void HandleInterruptRequest0x09();
                static void HandleInterruptRequest0x0A();
                static void HandleInterruptRequest0x0B();
                static void HandleInterruptRequest0x0C();
                static void HandleInterruptRequest0x0D();
                static void HandleInterruptRequest0x0E();
                static void HandleInterruptRequest0x0F();
                static void HandleInterruptRequest0x31();

                static void HandleInterruptRequest0x80();

                static void HandleException0x00();
                static void HandleException0x01();
                static void HandleException0x02();
                static void HandleException0x03();
                static void HandleException0x04();
                static void HandleException0x05();
                static void HandleException0x06();
                static void HandleException0x07();
                static void HandleException0x08();
                static void HandleException0x09();
                static void HandleException0x0A();
                static void HandleException0x0B();
                static void HandleException0x0C();
                static void HandleException0x0D();
                static void HandleException0x0E();
                static void HandleException0x0F();
                static void HandleException0x10();
                static void HandleException0x11();
                static void HandleException0x12();
                static void HandleException0x13();
                
                static hobbyos::common::uint32_t HandleInterrupt(hobbyos::common::uint8_t interrupt, hobbyos::common::uint32_t esp);
                hobbyos::common::uint32_t PerformHandleInterrupt(hobbyos::common::uint8_t interrupt, hobbyos::common::uint32_t esp);
                
                hobbyos::hardware::Port8BitSlow PICMasterCommandPort;
                hobbyos::hardware::Port8BitSlow PICMasterDataPort;
                hobbyos::hardware::Port8BitSlow PICSlaveCommandPort;
                hobbyos::hardware::Port8BitSlow PICSlaveDataPort;

            public:
                InterruptManager(hobbyos::common::uint16_t hardwareInterruptOffset, hobbyos::GlobalDescriptorTable* globalDescriptorTable);//, hobbyos::TaskManager* taskManager
                ~InterruptManager();
                hobbyos::common::uint16_t GetHardwareInterruptOffset();
                void Activate();
                void Deactivate();
        };
        
    }
}

#endif