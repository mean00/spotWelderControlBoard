#include "goPedal.h"
extern bool detectConnection();

Navigate *spawnGoPedal(Navigate *parent, Pedal &p)
{
    Navigate *gp= new GoPedal(parent,p);
    return gp;
}
bool GoPedal::start()
{
     _animationSkip=NB_ANIMATISKIP;
    _pedal.arm();
    return true;
}

bool GoPedal::triggered()
{
    bool detected=_pedal.pushed();
    return detected;
}
bool GoPedal::contact()
{
    return detectConnection();
}

/**
 * 
 */
void   GoPedal::automaton()
{
    switch(_state)
    {
        case Start:
            start();
            _state=Idle;
            break;   
        case  Idle:
            if(triggered())
            {
                _state=Pulsing; 
            }
            animate();
            return;
            break;            
        case  Pulsing:
            pulseBuzz();             
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
// EOF