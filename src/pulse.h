#pragma once
#include "lnTimer.h"
/**
 * 
 * @param timer
 * @param channel
 * @param pin
 */
class Pulse
{
public:
         Pulse(int timer, int channel, int pin);    
    void pulse(int durationMs);
    void interrupt();
protected:
    
    lnTimer         *_timer;
    int            _channel;
    int            _pin;
    
};