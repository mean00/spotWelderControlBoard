/**
 Use PWM + xDelay to generate a perfect pulse
 We program a PWM then stop it after only ~ one cycle to get a single pulse
 it only works because the times involved are big (i.e. cycle ~ 100 ms)
 
 */

#include "Arduino.h"
#include "MapleFreeRTOS1000_pp.h"
#include "pulse.h"

#define CYCLE_IN_MS 100
/**
 * 
 * @param timer
 * @param channel
 * @param pin
 */
 Pulse::Pulse(int timer, int channel, int pin)
    {
        _pin=pin;
        digitalWrite(_pin,0);
        lnPinMode(_pin,lnOUTPUT);        
        _timer=new lnTimer(timer,channel);
        _timer->setTimerFrequency(1000/CYCLE_IN_MS); // CYCLE_IN_MS ms end to end
        _channel=channel;        
    }

/**
 * 
 * @param durationMs
 */
void Pulse::pulse(int durationMs)
{
    if(durationMs>=(CYCLE_IN_MS*3/4))
        xAssert(0);

    noInterrupts();
    _timer->singleShot(durationMs);
    interrupts();
    xDelay((CYCLE_IN_MS*3)/4);
    digitalWrite(_pin,0);
    lnPinMode(_pin,lnOUTPUT);
}
/**
 * 
 */
void pulseDemo()
{    
    Pulse *p=new Pulse(3,1,PA6); // Timer 3  channel 1 PA6    
    while(1)
    {
        p->pulse(30);
        xDelay(10);
    }
    
}
//
