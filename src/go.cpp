#include "go.h"
#include "buzzer.h"
#include "pulse.h"



extern int pulseWidth;
/**
 * 
 */
void    GoBase::sendPulse()
{
    // Send pulse
    Pulse pulse(3,1,PIN_GATE); 
    pulse.pulse(pulseWidth);    
}
/**
 * 
 * @return 
 */
void GoBase::errorBuzz()
{
    for(int i=0;i<3;i++)
    {
         bz.buzz(8*1000,60);
         xDelay(60);
    }
}
/**
 * 
 */
void GoBase::pulseBuzz()
{
    for(int i=0;i<3;i++)
    {
        bz.buzz(2*1000,100);
        xDelay(100);
    }
}
/**
 * 
 */
void   GoBase::automaton()
{
    switch(_state)
    {
        case  Idle:
            if(triggered())
            {
                _state=Arming;
                _countDown=3;
            }
            break;
        case  Arming:
        {
            Logger("Arming =%d\n",_countDown);
            myScreen->redrawArmScreen( _countDown, _triggerSource, pulseWidth);
            bz.buzz(2*1000,300);
            int confirmed=0;
            for(int i=0;i<5;i++)
            {
                xDelay(100);
                confirmed+=contact();
            }
            Logger("confirmed =%d\n",confirmed);
            if(confirmed<4)
            {
                _state=Idle;
                errorBuzz();
                Logger("unconfirmed =%d\n",confirmed);
                return;
            }
            _countDown--;
            if(!_countDown)
            {
                myScreen->redrawArmScreen( 0, _triggerSource, pulseWidth);                
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
            _state=Idle;
            xDelay(2000);
            break;
        default:
            break;
    }
}
/**
 * 
 */
void GoBase::redraw()
{
    myScreen->redrawArmScreen( -1,  _triggerSource, pulseWidth);
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
            redraw();
            return NULL;
        default:
            xAssert(0);
            break;
            
    }
    return NULL;
}
