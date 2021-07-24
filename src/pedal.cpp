
#include "lnArduino.h"
#include "pedal.h"


#define THRESHOLD 200 // in ms

static void _myInterruptPedal(lnPin pin,void *a)
{
    Pedal *r=(Pedal *)a;
    r->interrupt();
}

/**
 * 
 */
Pedal::Pedal(int pin)
{
    _pin=pin;
    _state = 0;
    _pushed=0;
    _lastPush=0;
    lnPinMode(_pin,lnFLOATING);
}

/**
 * 
 * @return 
 */
bool Pedal::arm()
{
    lnExtiAttachInterrupt(_pin, LN_EDGE_RISING, _myInterruptPedal, this);
    return true;
}
/**
 * 
 */
#define ROUNDUP 0xffff
bool rd;
void Pedal::interrupt()
{
    rd=digitalRead(_pin);
    int now=millis()&ROUNDUP;
    if(now<_lastPush) now+=ROUNDUP+1;
    if((now-_lastPush)<THRESHOLD) 
    {
        return;
    }
    _lastPush=now&ROUNDUP;
    detachInterrupt(_pin);
    this->_pushed=1;
}

/**
 * 
 * @return 
 */
bool    Pedal::pushed()
{
    int evt = __atomic_exchange_n( &(this->_pushed), 0, __ATOMIC_SEQ_CST);
    if(evt)
    {
        Logger("Pedal!!\n");
    }
    return !!evt;
}

//
