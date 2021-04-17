#include "go.h"
#include "buzzer.h"
#include "pulse.h"
#include "assets.h"
extern bool detectConnection();
extern int pulseWidth;


const uint8_t *animation[NB_ANIMATION_STEP]={c4,c3,c2,c1,c1,c2,c3,c4};
/*
  int a=0;
  while(1)
  {
    myScreen->clear();
    myScreen->rleDisplay(c1_width, c1_height,1,1,animation[a]);
    myScreen->update();
    a=(a+1)&3;
    xDelay(100);
  }
 */
/**
 * 
 */
void    GoBase::sendPulse()
{
    // Send pulse
    myLeds->setEnable(false);
    Pulse pulse(GATE_TIMER,GATE_CHANNEL,PIN_GATE); 
    pulse.pulse(pulseWidth);    
    myLeds->setEnable(true);
}
/**
 * 
 * @return 
 */
void GoBase::errorBuzz()
{
    bz.buzz(600,800);
}
/**
 * 
 */
void GoBase::armingBuzz()
{
    bz.buzz(1*1000,300);
   
}
/**
 * 
 */
void GoBase::pulseBuzz()
{
    myScreen->clear();
    myScreen->print("PULSE",20,32+10);
    myScreen->update();
    for(int i=0;i<3;i++)
    {
        bz.buzz(3*1000,100);
        xDelay(100);
    }
    bz.buzz(2000,200);
}

void GoBase::goToStart()
{
    _state=Start;
    _animationStep=0;
    _animationSkip=NB_ANIMATISKIP;
}

/**
 * 
 */
void GoBase::redraw()
{
    
}
void GoBase::animate()
{
     _animationSkip--;
    if(_animationSkip<=0)
    {
        _animationSkip=NB_ANIMATISKIP;
        myScreen->clear();
        myScreen->redrawArmScreen( -1,  _triggerSource, pulseWidth);
        myScreen->rleDisplay(c1_width,c1_height,1,1,animation[_animationStep]);
        myScreen->update();
        _animationStep=(_animationStep+1)%NB_ANIMATION_STEP;
    }
}
Navigate *GoBase::handleEvent(Event evt,bool &subMenu)
{
    if( getCurrentVbat()< MIN_VBAT)
    {
        myScreen->clear();
        myScreen->print("Low Volt",8,40);
        myScreen->update();
        errorBuzz();
        errorBuzz();
        subMenu=false;
        return _parent;
    }
    
    switch(evt)
    {
        case Navigate::E_PUSH:
            subMenu=false;
            return _parent;
        case Navigate::E_TIMER:
            automaton();
            return NULL;
        default:
            xAssert(0);
            break;
            
    }
    return NULL;
}
/**
 * 
 * @param p
 * @param source
 */
 GoBase::GoBase(Navigate *p, Welder::TriggerSource  source) : Navigate(p), bz(BUZZER_GATE)
            {
                _state=Start;
                _triggerSource=source;
                _animationStep=0;
                _animationSkip=NB_ANIMATISKIP;
                myLeds->setArmState(true);
            }
 
GoBase::~GoBase()
{
    myLeds->setArmState(false);
}