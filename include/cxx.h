#ifndef CXX_H
#define CXX_H

#include <cstdint>

// Allocating and freeing memory require passing an id to `__memAlloc` and `__memFree` respectively, so using separate functions
// to call those with the specified id uses less memory when they are used a lot
void *allocMemory(std::size_t size);
void freeMemory(void *ptr);

// Inline all new/delete operators, as doing so allows the compiler to exclude unused variables from them, and also makes the
// assembly easier to follow. Note that doing this means that this header will need to be included in any other file that uses
// these operators.
inline void *operator new(std::size_t size)
{
    return allocMemory(size);
}

inline void *operator new[](std::size_t size)
{
    return allocMemory(size);
}

inline void operator delete(void *ptr)
{
    return freeMemory(ptr);
}

inline void operator delete[](void *ptr)
{
    return freeMemory(ptr);
}

inline void operator delete(void *ptr, std::size_t size)
{
    (void)size;
    return freeMemory(ptr);
}

inline void operator delete[](void *ptr, std::size_t size)
{
    (void)size;
    return freeMemory(ptr);
}

#endif
