#include "draw.h"
#include "patch.h"
#include "gc/OSArena.h"
#include "ttyd/dispdrv.h"
#include "ttyd/fontmgr.h"
#include "ttyd/mariost.h"

#include <cstdint>

// Used for hooking `marioStMain` via `hookFunction`. When `marioStMain` is hooked, all instances of it being called in the
// vanilla game will be replaced with `runOncePerFrame`. In order to actually call the original function,
// `g_marioStMain_trampoline` can simply be called at any point. Note that the variable and replacement function used for hooks
// are required to have their parameter types and return type perfectly match the function that is being hooked. Set to `static`
// since it is only used in this cpp file, and making it static allows the compiler to apply more optimizations to it.
static void (*g_marioStMain_trampoline)();

// In TTYD specifically, things that are drawn onto the screen are handled at a specific time, in which functions for handling
// this are intended to be added to a list of ones to run each frame. The function `dispEntry` is used for registering any given
// function for this, so `drawHelloWorld` will be set up for that. Set to `static` since it is only used in this cpp file, and
// making it static allows the compiler to apply more optimizations to it.
static void drawHelloWorld(CameraId cameraId, void *user)
{
    // `cameraId` and `user` are not needed for this function
    (void)cameraId;
    (void)user;

    // Draw the text at the top-left of the screen under the status window
    const char *text = "Hello World";
    drawText(text, -232.f, 120.f, 0.7f, getColorWhite(0xFF));
}

// Main function that will run exactly once per frame in the vanilla game's main loop. Set to `static` since it is only used in
// this cpp file, and making it static allows the compiler to apply more optimizations to it.
static void runOncePerFrame()
{
    // Register `drawHelloWorld` to run when the vanilla game's drawing functions run
    drawOnDebugLayer(drawHelloWorld, 0.f);

    // Finished running all of the desired code, so call the original function to allow the vanilla game to properly progress.
    // Note that this could instead be called first to have the vanilla code run before this project's code, and additioanl code
    // could also be added after this call as well.
    g_marioStMain_trampoline();
}

// Generic function for initializing the project, as this code will run at different times depending on what version of the `REL
// Loader` is used to load it. Set to `static` since it is only used in this cpp file, and making it static allows the compiler
// to apply more optimizations to it.
static uint32_t initMod()
{
    // Initialize text stuff early, so that text can be drawn immediately
    fontmgrTexSetup();

    // Replace the first instruction in `fontmgrTexSetup` with `blr`, which effectively prevents the function from running later
    // when it was originally supposed to
    constexpr uint32_t blrValue = 0x4E800020;
    applyAssemblyPatch(fontmgrTexSetup, blrValue);

    // This project will just draw some text onto the screen once per frame, so hook `marioStMain` since that runs at the start
    // of the game's main loop and runs exactly once per frame
    g_marioStMain_trampoline = hookFunction(marioStMain, runOncePerFrame);

    // If this function was hooked at the address where `v1` or `v2` would normally run, then the original instruction at that
    // address set `r3` to `0`. This functionality can be restored by simply having this function return 0.
    return 0;
}

// Entry point into the project, which is called by `_prolog`. Runs exactly once at boot when the REL is initially loaded.
void init()
{
    // Check which version of the `REL Loader` was used to load this project. This project is set up to be able to allocate/free
    // memory using the game's vanilla functions, so if `v3` of the `REL Loader` is used, then the initial hook location must be
    // different.
    if (__OSArenaLo == __OSArenaHi)
    {
        // Not using `v3`, so initialize stuff now
        initMod();
    }
    else
    {
        // Using `v3`, so hook at the address where `v1` and `v2` would normally run
#ifdef TTYD_US
        constexpr uint32_t marioStInitAddress = 0x8006FE38;
#elif defined TTYD_JP
        constexpr uint32_t marioStInitAddress = 0x8006EBD8;
#elif defined TTYD_EU
        constexpr uint32_t marioStInitAddress = 0x800710F4;
#endif
        writeBranchBL(marioStInitAddress, initMod);
    }
}

// Exit point from the project, which is called by `_epilog`. Runs exactly once just before the REL is unloaded (if this ever
// actually occurs). Due to the way `rel.cpp` is set up, this function is required to always exist, even if it doesn't do
// anything.
void exit() {}
