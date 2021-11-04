// 
//
#include "lnArduino.h"
#include "gfxfont.h"
//#include "assets/fonts/Fonts/FontsFree_Net_Nurom_Bold9pt7b.h"
#include "assets/fonts/Fonts/FreeSansBold9pt7b.h"
#include "assets/fonts/Fonts/FreeSansBold20pt7b.h"

const GFXfont *getFont(int index)
{
    switch(index)
    {
        case 0: return &FreeSansBold9pt7b;break;
        case 1: return &FreeSansBold20pt7b;break;
        case 2: return &FreeSansBold20pt7b;break;
        default: xAssert(0);break;
    }
    xAssert(0);
    return NULL;
}

