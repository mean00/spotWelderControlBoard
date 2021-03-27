#include "Arduino.h"
#include "buzzer.h"
#include "MapleFreeRTOS1000_pp.h"
#include "myPwm.h"
/**
 * 
 * @param pin
 */
Buzzer::Buzzer(int pin)
{
    _pin=pin;
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,0);
}
/**
 * 
 */
Buzzer::~Buzzer()
{

}
/**
 * 
 * @param frequency
 * @param durationMs
 * @return 
 */
bool Buzzer::buzz(int frequency, int durationMs)
{   
#if 0
    int halfCyle=500000/frequency; // number of us
    if(!halfCyle) halfCyle=1;
    int m=millis();
    m&=0xffff;
    while(1)
    {
        digitalWrite(_pin,1);
        delayMicroseconds(halfCyle);
        digitalWrite(_pin,0);
        delayMicroseconds(halfCyle);
        int t=millis()&0xffff;
        if(t<m) t+=0x10000;
        if((t-m)>durationMs)
            return true;
    }
#else
     pinMode(_pin,PWM);
     myPwm(_pin,frequency);
     pwmRestart(_pin);
     xDelay(durationMs);
     pwmWrite(_pin,0);
#endif
    return true;
}

// EOF