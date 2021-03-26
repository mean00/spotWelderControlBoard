
#pragma once
#include "navigate.h"
#include "welderUi.h"
#include "buzzer.h"
#include "pinMapping.h"
/**
 * 
 * @param p
 */
class GoBase : public Navigate
{
public:
    enum State
    {
        Idle,
        Arming,
        Pulsing,
        Pulsed
    };
  
    
            GoBase(Navigate *p) : Navigate(p), bz(BUZZER_GATE)
            {
                _state=Idle;
            }
    virtual ~GoBase()
            {

            }
    virtual bool triggered()=0;
    virtual Navigate *handleEvent(Event evt,bool &subMenu);
    virtual void  handleRotary(int inc) {}
            void  automaton();
    virtual bool contact()=0;
    virtual void redraw();

protected:
    void    sendPulse();
    State   _state;
    int     _countDown;
    Buzzer  bz;
    
};