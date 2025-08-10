#include "cxx.h"
#include "ttyd/memory.h"

#include <cstdint>

void *allocMemory(std::size_t size)
{
    return __memAlloc(HeapType::HEAP_DEFAULT, size);
}

void freeMemory(void *ptr)
{
    return __memFree(HeapType::HEAP_DEFAULT, ptr);
}
