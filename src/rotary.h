


class Rotary
{
public:
            Rotary(int left, int right, int push);
    bool    setup();
    void    interruptRE();
    void    interruptPush();
    int     getRotaryValue();
    int     getPush();

protected:
    int     _pinL, _pinR, _pinPush;
    int     _counter;
    int     _state;
    int     _lastPush;
    volatile int     _pushed;
};
// EOF

