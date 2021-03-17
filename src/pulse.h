#pragma once
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
    
    HardwareTimer *_timer;
    int            _channel;
    int            _pin;
    
};