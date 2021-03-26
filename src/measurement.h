#include "adc/simpleADC.h"
#include "MapleFreeRTOS1000_pp.h"
/**
 */
#define NB_DETECT 4
class Measurement: public xTask
{
    public:
                            Measurement(int pinV,int pinD);
                     void   run();
                     int    getPinV() {return _valueV;}
                     int    getPinD() {return _valueD;}
                     float  vcc() {return _vcc;}
                     bool   detected() {return _detected;}
    protected:
                     int  _pinV,_pinD;
                     int  _valueV,_valueD;
                     simpleAdc *_adc;
                     float     _vcc;
                     int       _avgDetect[NB_DETECT];
                     int       _dex;
                     bool      _detected;
};