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
    }

/**
 * 
 * @param durationMs
 */
void Pulse::pulse(int durationMs)
{
    if(durationMs>=(CYCLE_IN_MS*3/4))
        xAssert(0);
    
    lnPinMode(_pin,lnALTERNATE_PP);   
    _timer->singleShot(durationMs); // off by 2%
    digitalWrite(_pin,0);
    lnPinMode(_pin,lnOUTPUT);
}
/**
 * 
 */
void pulseDemo()
{    
    Pulse *p=new Pulse(2,3,PB1); // Timer 3  channel 1 PA6    
    
    while(1)
    {
        lnPinMode(PB1,lnALTERNATE_PP);   
        p->pulse(5);    
        xDelay(100);

        p->pulse(5);    
        xDelay(100);
        p->pulse(5);    
        xDelay(200);

    }
    
}
//
