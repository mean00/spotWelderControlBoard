#include "lnArduino.h"
#include "lnTimer.h"
#include "buzzer.h"


/**
 * 
 * @param pin
 */
Buzzer::Buzzer(int pin)
{
    _pin=pin;
    lnPinMode(_pin,lnOUTPUT);
    lnDigitalWrite(_pin,0);
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
     lnPinMode(_pin,lnPWM);
     
     lnTimer pwm(_pin);
     pwm.setPwmFrequency(frequency);
     pwm.setPwmMode(512);
     pwm.enable();
     xDelay(durationMs);
     pwm.setPwmMode(0);
     pwm.disable();
     lnPinMode(_pin,lnOUTPUT);
     lnDigitalWrite(_pin,0);
     return true;
}

// EOF