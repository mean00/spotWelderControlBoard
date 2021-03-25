
#pragma once
#include "navigate.h"
#include "welderUi.h"
/**
 * 
 * @param p
 */
class TriggerSelection : public Navigate
{
public:
  
    
            TriggerSelection(Navigate *p);                
    virtual ~TriggerSelection();
    virtual Navigate *handleEvent(Event evt,bool &subMenu);
    virtual void redraw();
    virtual void  handleRotary(int inc);

    Welder::TriggerSource   _source;
    
};