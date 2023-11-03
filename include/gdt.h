#ifndef __HOBBYOS__GDT_H
#define __HOBBYOS__GDT_H

#include <common/types.h>

namespace hobbyos
{
    class SegmentDescriptor
    {
        private:
            hobbyos::common::uint16_t limit_low;
            hobbyos::common::uint16_t base_low;
            hobbyos::common::uint8_t base_mid;
            hobbyos::common::uint8_t type_and_flags;
            hobbyos::common::uint8_t limit_high_and_flags;
            hobbyos::common::uint8_t base_high;

        public:
            SegmentDescriptor(hobbyos::common::uint32_t base, hobbyos::common::uint32_t limit, hobbyos::common::uint8_t type);
            hobbyos::common::uint32_t GetBase();
            hobbyos::common::uint32_t GetLimit();

    } __attribute__((packed));

    class GlobalDescriptorTable
    {
        
        public:

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();
            void LoadLGDTRegister();
            
            

            

            hobbyos::common::uint16_t GetCodeSegmentSelector();
            hobbyos::common::uint16_t GetDataSegmentSelector();
    };

    extern "C"
            {
                void ASM_LGDT_ReloadSegReg(hobbyos::common::uint32_t *);
            }
}

#endif