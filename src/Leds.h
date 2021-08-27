

class WelderLeds
{
public:
                WelderLeds(lnPin pin);               
        void    setProbeDetectState(bool onoff);
        void    setArmState(bool onoff);    
        void    setEnable(bool onoff);    
        void    single(bool value, int dex,  int r, int g , int b);
protected:
        void    update(void);
        bool    _enabled;
        bool    _armed;
        bool    _voltageDetect;
        lnPin   _pin;
        void    *_ws;
};
