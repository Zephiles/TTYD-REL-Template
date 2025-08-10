#ifndef GC_OSARENA_H
#define GC_OSARENA_H

#include <cstdint>

// Functions/variables that are directly from the game need to be in `extern "C"` blocks to prevent their names from being
// mangled, so that their entry can be found in the lst
extern "C"
{
    // In addition to needing to be in an `extern "C"` block, variables also need to be labeled as `extern`
    extern void *__OSArenaLo;
    extern void *__OSArenaHi;
}

#endif
