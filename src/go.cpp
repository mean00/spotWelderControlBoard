#include "go.h"
#include "buzzer.h"
#include "pulse.h"

extern bool detectConnection();

extern int pulseWidth;
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
                _state=Idle;
                errorBuzz();
                Logger("unconfirmed =%d\n",confirmed);
                return;
            }
            _countDown--;
            if(!_countDown)
            {
                if(!contact())
                {
                    _state=Idle;
                    errorBuzz();
                    Logger("unconfirmed =%d\n",confirmed);
                    return;
                }
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
            if(detectConnection())
            {
                myScreen->disconnectMessage();
                return;
            }
            _state=Idle;            
            break;
        case WaitingToRearm:
            xDelay(200);
            break;
        default:
            break;
    }
    myScreen->redrawArmScreen( -1,  _triggerSource, pulseWidth);
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
            redraw();
            return NULL;
        default:
            xAssert(0);
            break;
            
    }
    return NULL;
}
