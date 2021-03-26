#include "go.h"
#include "buzzer.h"
#include "pulse.h"



extern int pulseWidth;
/**
 * 
 */
void    GoBase::sendPulse()
{
    // Send double buzz quickly    
    bz.buzz(10000,200);
    xDelay(500);
    bz.buzz(10000,200);
    // Send pulse
    Pulse pulse(3,1,PIN_GATE); 
    pulse.pulse(pulseWidth);    
}
/**
 * 
 * @return 
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
            bz.buzz(10000,200);
            int confirmed=0;
            for(int i=0;i<5;i++)
            {
                xDelay(100);
                confirmed+=contact();
            }
            if(confirmed<4)
            {
                _state=Idle;
                for(int i=0;i<2;i++)
                {
                     bz.buzz(10000,100);
                     xDelay(100);
                }
                return;
            }
            _countDown--;
            if(!_countDown)
            {
                _state=Pulsing;
            }
        }
            break;
        case  Pulsing:
            sendPulse();
            _state=Pulsed;
            break;
        case  Pulsed:
            _state=Idle;
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
    myScreen->redrawArmScreen( getCurrentVbat(), _triggerSource, pulseWidth);
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
