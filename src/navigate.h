
#pragma once


#include <Wire.h>
#include "screen.h"
#include "MapleFreeRTOS1000_pp.h"
#include "printf.h"
#include "dso_debug.h"
#include "navigate.h"
#include "vector"

extern float getCurrentVbat();

class Navigate
{
public:
    enum Event
    {
        E_PUSH=1,
        E_TIMER=2
    };
                Navigate(Navigate *p)
                {
                    _parent=p;
                }
    virtual ~Navigate() {_parent=NULL;}
    virtual Navigate *handleEvent(Event evt,bool &subMenu)=0;
    virtual void  handleRotary(int inc)=0;
    virtual void redraw()=0;
protected:
    Navigate     *_parent;
};

extern MyScreen *myScreen;