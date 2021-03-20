


class Rotary
{
public:
            Rotary(int left, int right, int push);
    bool    setup();
    void    interruptRE();
    void    interruptPush();
    int     getRotaryValue();
    bool    getPush();

protected:
    int     _pinL, _pinR, _pinPush;
    int     _counter;
    bool    _push;
    int     _state;
    int     _lastPush;
    bool    _pushed;
};
// EOF

