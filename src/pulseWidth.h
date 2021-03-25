
#pragma once
#include "navigate.h"
#include "welderUi.h"
/**
 * 
 * @param p
 */
class PulseWidth : public Navigate
{
public:
  
    
            PulseWidth(Navigate *p);                
    virtual ~PulseWidth();
    virtual Navigate *handleEvent(Event evt,bool &subMenu);
    virtual void redraw();
    virtual void  handleRotary(int inc);

    int   _pulseWidth;
    
};