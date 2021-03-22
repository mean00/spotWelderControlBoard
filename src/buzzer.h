
#pragma once


class Buzzer
{
public:
             Buzzer(int pin);
    virtual ~Buzzer();
        bool buzz(int frequency, int durationMs);
        

protected:    
        int _pin;
        
    
};