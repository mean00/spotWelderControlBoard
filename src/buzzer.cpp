#include "Arduino.h"
#include "buzzer.h"
#include "MapleFreeRTOS1000_pp.h"
/**
 * 
 * @param pin
 */
Buzzer::Buzzer(int pin)
{
    _pin=pin;
    pinMode(_pin,PWM);
    pwmWrite(pin,0);    
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
    pwmWrite(_pin,127*256);
    xDelay(durationMs);
    pwmWrite(_pin,0);
}

// EOF