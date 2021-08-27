#include "go.h"
#include "buzzer.h"
#include "pulse.h"
#include "assets.h"
extern bool detectConnection();
extern int pulseWidth;

#if 0
const uint8_t *animation[NB_ANIMATION_STEP]={sp0001,sp0002,sp0003,sp0004,
sp0005,sp0006,sp0007,sp0008,sp0009};
#else 
const uint8_t *animation[NB_ANIMATION_STEP]={sp0001,sp0003,sp0005,sp0007,sp0009};
#endif
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

bool GoBase::endPulse()
{
    if(detectConnection())
    {
        myScreen->disconnectMessage();
        return true;
    }

    myScreen->clear();
    xDelay(1000); // Let voltage recover
    goToStart();           
    return false;
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
#if 1
        myScreen->rleDisplay(sp0001_width,sp0001_height-1,
                             2,2,animation[_animationStep]
                            );
#endif     
        myScreen->update();
        _animationStep=(_animationStep+1);
        if(_animationStep>=NB_ANIMATION_STEP) _animationStep=0;
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
