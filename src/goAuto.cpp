#include "goAuto.h"
extern bool detectConnection();

Navigate *spawnGoAuto(Navigate *parent)
{
    return new GoAuto(parent);
}
bool GoAuto::start()
{
    detectConnection();
    return true;
}
bool GoAuto::triggered()
{
    bool detected=detectConnection();
    if(detected)
    {
        _detectionCounter++;
        if(_detectionCounter>10)
            return true;
        return false;
    }
    // reset
    _detectionCounter=0;
    return false;
}
bool GoAuto::contact()
{
    return detectConnection();
}

/**
 * 
 */
void   GoAuto::automaton()
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
            animate();
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
                  
            }
        }
            break;
        case  Pulsing:
            pulseBuzz();             
            sendPulse();
            _state=Pulsed;
            break;
        case  Pulsed:
            if(endPulse()) return;
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
// EOF