#include "navigate.h"
#include "dso_eeprom.h"
#include "trigger.h"
#include "welderTypes.h"
extern TriggerSource triggerSource;
/**
 * 
 * @param p
 */
TriggerSelection::TriggerSelection(Navigate *p): Navigate(p)
{
    _source=triggerSource;
    redraw();
}
/**
 * 
 */
TriggerSelection::~TriggerSelection()
{
   
}

/**
 * 
 */
void TriggerSelection::redraw()
{
    myScreen->clear();
    myScreen->print("Input",2,20);        
    if(_source==Pedal)
        myScreen->printBig("Pedal",2,60);
    else
        myScreen->printBig("Auto",2,60);
    myScreen->update();
}
/**
 * 
 * @param inc
 */
void  TriggerSelection::handleRotary(int inc)
{
    int s=(int )_source;
    s+=inc;
    s=(s+256)&1;
    _source=(TriggerSource)s;
    redraw();
}

Navigate *TriggerSelection::handleEvent(Event evt,bool &subMenu)
{
    switch(evt)
    {
        case Navigate::E_PUSH:
            triggerSource=_source;
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

Navigate *spawnTrigger(Navigate *parent)
{
    return new TriggerSelection(parent);
}