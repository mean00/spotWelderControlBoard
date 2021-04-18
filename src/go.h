
#pragma once
#include "navigate.h"
#include "welderUi.h"
#include "buzzer.h"
#include "pinMapping.h"
#include "Leds.h"

#define NB_ANIMATISKIP    4 // refresh screen every SKIP
#define NB_ANIMATION_STEP 9
extern WelderLeds *myLeds;
/**
 * 
 * @param p
 */
class GoBase : public Navigate
{
public:
            enum State
            {
                Start,
                Idle,
                Arming,
                Pulsing,
                Pulsed,
                WaitingToRearm
            };
  
    
            GoBase(Navigate *p, Welder::TriggerSource  source) ;           
    virtual ~GoBase();
           
    virtual bool        triggered()=0;
    virtual Navigate    *handleEvent(Event evt,bool &subMenu);
    virtual void        handleRotary(int inc) {}
    virtual bool        contact()=0;
    virtual bool        start()=0;
    virtual void        redraw();
    virtual bool        endPulse();

protected:
    void        animate();
    void        sendPulse();
    void        errorBuzz();
    void        pulseBuzz();
    void        armingBuzz();
    void        goToStart();
 virtual void   automaton()=0;
    State       _state;
    int         _countDown;
    Buzzer      bz;
    Welder::TriggerSource _triggerSource;
    int         _animationStep,_animationSkip;
    
};

extern int pulseWidth;