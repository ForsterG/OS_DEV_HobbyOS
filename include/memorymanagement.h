#ifndef __HOBBYOS__MEMORYMANAGEMENT_H
#define __HOBBYOS__MEMORYMANAGEMENT_H

#include <common/types.h>


namespace hobbyos
{
    
    struct MemoryChunk
    {
        MemoryChunk *next;
        MemoryChunk *prev;
        bool allocated;
        common::size_t size;
    };
    
    
    class MemoryManager
    {
        
    protected:
        MemoryChunk* first;
    public:
        
        static MemoryManager *activeMemoryManager;
        
        MemoryManager(common::size_t first, common::size_t size);
        ~MemoryManager();
        
        void* malloc(common::size_t size);
        void free(void* ptr);
    };
}

void* operator new(hobbyos::common::size_t size);
void* operator new[](hobbyos::common::size_t size);

// placement new
void* operator new(hobbyos::common::size_t, void* ptr);
void* operator new[](hobbyos::common::size_t, void* ptr);

void operator delete(void* ptr);
void operator delete[](void* ptr);


#endif