


class Rotary
{
public:
            Rotary(int left, int right, int push);
    bool    setup();
    void    interruptRE();
    int     getRotaryValue();

protected:
    int _pinL, _pinR, _pinPush;
    int _counter;
    bool _push;
    int _state;

};
