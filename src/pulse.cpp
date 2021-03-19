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
        pinMode(_pin,OUTPUT);        
        _timer=new HardwareTimer(timer);
        _timer->init();
        _timer->pause();
        _timer->setPeriod(CYCLE_IN_MS*1000); // CYCLE_IN_MS ms end to end
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
    _timer->pause();
    int ovf=_timer->getOverflow();
   
    int count=(durationMs*ovf)/CYCLE_IN_MS;
    
    noInterrupts();
    _timer->setCompare(_channel,count);
    _timer->refresh();
    pinMode(_pin,PWM);
    _timer->resume();
    interrupts();
    xDelay((CYCLE_IN_MS*3)/4);
    _timer->pause();
    digitalWrite(_pin,0);
    pinMode(_pin,OUTPUT);
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
