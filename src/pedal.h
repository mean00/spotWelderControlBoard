#pragma once
/**
 * \brief Single shot pedal managemen
 */
class Pedal
{
public:
            Pedal(int pin);
    bool    arm();
    bool    pushed();
    void    interrupt();
protected:
    int     _pin;
    int     _lastPush;
    int     _state;    
    volatile int     _pushed;
};