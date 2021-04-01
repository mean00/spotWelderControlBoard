#pragma once
class Pedal
{
public:
            Pedal(int pin);
    bool    setup();
    bool    pushed();
    void    interrupt();
protected:
    int     _pin;
    int     _lastPush;
    int     _state;    
    volatile int     _pushed;
};