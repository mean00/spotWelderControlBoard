#include "navigate.h"
#include "dso_eeprom.h"
#include "pulseWidth.h"

extern int pulseWidth;
/**
 * 
 * @param p
 */
PulseWidth::PulseWidth(Navigate *p): Navigate(p)
{
   
    _pulseWidth=pulseWidth;
    redraw();
}
/**
 * 
 */
PulseWidth::~PulseWidth()
{
   
}
extern int getVBat10(int offset);

/**
 * 
 */
void PulseWidth::redraw()
{
    char tmp[16];
    sprintf(tmp,"%02d",_pulseWidth);    
    myScreen->clear();
    myScreen->printBig(tmp,4,60);
    myScreen->update();
}
/**
 * 
 * @param inc
 */
void  PulseWidth::handleRotary(int inc)
{
    redraw();
}

Navigate *PulseWidth::handleEvent(Event evt,bool &subMenu)
{
    switch(evt)
    {
        case Navigate::E_PUSH:
            pulseWidth=_pulseWidth;
            subMenu=false;
            return _parent;
        case Navigate::E_TIMER:
            redraw();
            return NULL;
        default:
            xAssert(0);
            break;
            
    }
    return NULL;
}
Navigate *spawnPulseWidth(Navigate *parent)
{
    return new PulseWidth(parent);
}