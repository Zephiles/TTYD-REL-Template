#ifndef TTYD_MARIOST_H
#define TTYD_MARIOST_H

#include <cstdint>

// Functions/variables that are directly from the game need to be in `extern "C"` blocks to prevent their names from being
// mangled, so that their entry can be found in the lst
extern "C"
{
    void marioStInit();
    void marioStMain();
    void marioStDisp();
    void marioStSystemLevel(int32_t level);
    uint32_t marioStGetSystemLevel();
    void viPostCallback(uint32_t retraceCount);
    void gcDvdCheckThread();
    void gcRumbleCheck();
    // L_gcResetCheck
    // N_systemErrorHandler
    // N_setupErrorHandler
}

#endif
