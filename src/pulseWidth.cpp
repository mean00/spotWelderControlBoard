#include "navigate.h"
#include "dso_eeprom.h"
#include "pulseWidth.h"
#include "pinMapping.h"
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
    myScreen->print("PulseWidth",20,20);
    myScreen->printBig(tmp,4,60);
    myScreen->update();
}
/**
 * 
 * @param inc
 */
void  PulseWidth::handleRotary(int inc)
{
    int tmp=_pulseWidth;
    tmp+=inc;
    if(tmp<MIN_PULSE) tmp=MIN_PULSE;
    if(tmp>MAX_PULSE) tmp=MAX_PULSE;
    _pulseWidth=tmp;
    redraw();
}

Navigate *PulseWidth::handleEvent(Event evt,bool &subMenu)
{
    switch(evt)
    {
        case Navigate::E_PUSH:
            pulseWidth=_pulseWidth;
            DSOEeprom::writePulse(pulseWidth);
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