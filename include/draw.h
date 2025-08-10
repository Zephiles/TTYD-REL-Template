#ifndef DRAW_H
#define DRAW_H

#include "ttyd/fontmgr.h"
#include "ttyd/dispdrv.h"

#include <cstdint>

// Misc colors and functions to get said colors
#define COLOR_WHITE 0xFFFFFF00
#define COLOR_BLACK 0x00000000
#define COLOR_BLUE 0x5B59DE00
#define COLOR_GREEN 0x1BBE2300
#define COLOR_RED 0xFF141400

// Inline the color functions to allow the compiler to simply combine the values without doing an actual function call to handle
// it
inline uint32_t getColorWhite(uint8_t alpha)
{
    return COLOR_WHITE | alpha;
}

inline uint32_t getColorBlack(uint8_t alpha)
{
    return COLOR_BLACK | alpha;
}

inline uint32_t getColorBlue(uint8_t alpha)
{
    return COLOR_BLUE | alpha;
}

inline uint32_t getColorGreen(uint8_t alpha)
{
    return COLOR_GREEN | alpha;
}

inline uint32_t getColorRed(uint8_t alpha)
{
    return COLOR_RED | alpha;
}

// Inline `drawTextInit` to allow the compiler to exclude unused variables from them and to only call the functions that are
// actually used
inline void drawTextInit(bool drawFontEdge, uint8_t alpha)
{
    // If the alpha is 0xFF, then just call `FontDrawStart` since that already initializes the alpha to 0xFF
    if (alpha == 0xFF)
    {
        FontDrawStart();
    }
    else
    {
        FontDrawStart_alpha(alpha);
    }

    // `FontDrawStart`/`FontDrawStart_alpha` initialize the font edge to be off, so enable it if necessary
    if (drawFontEdge)
    {
        FontDrawEdge();
    }
}

void drawOnDebugLayer(DispCallback func, float order);
void drawText(const char *text, float posX, float posY, float scale, uint32_t color);

#endif
