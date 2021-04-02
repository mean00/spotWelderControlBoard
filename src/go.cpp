#include "go.h"
#include "buzzer.h"
#include "pulse.h"
#include "assets.h"
extern bool detectConnection();
extern int pulseWidth;

#define NB_ANIMATISKIP    4 // refresh screen every SKIP
#define NB_ANIMATION_STEP 8
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
    Pulse pulse(GATE_TIMER,GATE_CHANNEL,PIN_GATE); 
    pulse.pulse(pulseWidth);    
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
    
   
    for(int i=0;i<3;i++)
    {
        bz.buzz(3*1000,100);
        xDelay(100);
    }
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
void   GoBase::automaton()
{
    switch(_state)
    {
        case Start:
            start();
            _state=Idle;
            return;
            break;
        case  Idle:
            if(triggered())
            {
                _state=Arming;
                _countDown=3;            
            }
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
            return;
            break;
        case  Arming:
        {
            Logger("Arming =%d\n",_countDown);
            myScreen->redrawArmScreen( _countDown, _triggerSource, pulseWidth);
            myScreen->update();
            armingBuzz();
            int confirmed=0;
            for(int i=0;i<5;i++)
            {
                xDelay(100);
                confirmed+=contact();
            }
            Logger("confirmed =%d\n",confirmed);
            if(confirmed<4)
            {
                goToStart();
                errorBuzz();
                Logger("unconfirmed =%d\n",confirmed);
                return;
            }
            _countDown--;
            if(!_countDown)
            {
                if(!contact())
                {
                    goToStart();
                    errorBuzz();
                    Logger("unconfirmed =%d\n",confirmed);
                    return;
                }
                myScreen->redrawArmScreen( 0, _triggerSource, pulseWidth);                
                myScreen->update();
                _state=Pulsing;
                pulseBuzz();                
            }
        }
            break;
        case  Pulsing:
            sendPulse();
            _state=Pulsed;
            break;
        case  Pulsed:
            if(detectConnection())
            {
                myScreen->disconnectMessage();
                return;
            }
            goToStart();           
            break;
        case WaitingToRearm:
            xDelay(200);
            break;
        default:
            break;
    }
    myScreen->redrawArmScreen( -1,  _triggerSource, pulseWidth);
    myScreen->update();
}
/**
 * 
 */
void GoBase::redraw()
{
    
}

Navigate *GoBase::handleEvent(Event evt,bool &subMenu)
{
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
