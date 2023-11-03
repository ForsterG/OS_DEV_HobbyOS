#include <gdt.h>
using namespace hobbyos;
using namespace hobbyos::common;


#include <hardware/vga.h>
using namespace hobbyos::hardware;

GlobalDescriptorTable::GlobalDescriptorTable()
    :   nullSegmentSelector(0xFFFFFFFF, 0, 0),
        codeSegmentSelector(0x0,0xFFFFFF, 0xA),
        dataSegmentSelector(0x0, 0xFFFFFF, 0x3)
{
}

void GlobalDescriptorTable::LoadLGDTRegister()
{
    uint32_t i[2];
    i[0] = ((uint32_t) sizeof(GlobalDescriptorTable))<<16;//6 bytes??? structure reversed inside the manual???
    i[1] = (uint32_t) (this); 

    ASM_LGDT_ReloadSegReg(i);
}



GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16_t GlobalDescriptorTable::GetDataSegmentSelector()
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::GetCodeSegmentSelector()
{
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}



SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type)//00cf9a (code) and 00cf93 (data)
{
    this->base_low = (uint16_t)(base & 0xFFFF);
    this->base_mid = (uint8_t)((base & 0xFF0000)>>16);
    this->base_high = (uint16_t)((base & 0xFF000000)>>24);

    this->limit_low =(uint16_t)(limit & 0xFFFF);

    uint8_t limit_temp = (uint8_t)((limit & 0xF0000)>>16) | 0b11000000; //Granularity, Default operand size (D/B), Reserved (0), Available to software(AVL)
    this->limit_high_and_flags = limit_temp;

    this->type_and_flags = (uint8_t) type | 0b10010000;//P(should not be set), DPL,S

}

uint32_t SegmentDescriptor::GetBase()
{
    uint32_t base = ((uint32_t)(this->base_high))<<24;
    base = (((uint32_t)(this->base_mid))<<16) | base;
    base = ((uint32_t)(this->base_low)) | base;
    return base;
}

uint32_t SegmentDescriptor::GetLimit()
{
    uint32_t limit = ((uint32_t)(this->limit_high_and_flags & 0x0F))<<16;
    limit = (((uint32_t)(this->limit_low))) | limit;
    return limit;
}

