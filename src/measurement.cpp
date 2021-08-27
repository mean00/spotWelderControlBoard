

#include "lnArduino.h"
#include "measurement.h"

#define DETECT_THRESHOLD 1000
/**
 * 
 * @param pinV
 * @param pinD
 */
Measurement::Measurement(int pinV,int pinD) : xTask("MEASURE",  4, 300)
{

  lnPinMode(pinV,lnADC_MODE);
  lnPinMode(pinD,lnADC_MODE);
  _adc=new lnTimingAdc(0);
  
  _pinV=pinV;
  _pinD=pinD;
  for(int i=0;i<NB_DETECT;i++)  
      _avgDetect[i]=0;
  _dex=0;
  _detected=false;
  _pins[0]=_pinV;
  _pins[1]=_pinD;
  _adc->setSource(3,3,1000,2,_pins);
#warning VREF seems unreliable
#if 0
  _vcc=_adc->getVcc();  
#else
  _vcc=3300;  
#endif
  start();
}
/**
 * 
 */
int skip=0;
void Measurement::run()
{
  
  uint16_t   out[48*2];
  while(1)
  {   
      int nb=32;
      xAssert(_adc->multiRead(nb,out));
      int vbat=0, detect=0;
      uint16_t *data=out;
      for(int i=0;i<nb;i++)
      {
          vbat+=data[0];
          detect+=data[1];
          data+=2;
      }
      vbat=(vbat)/nb;
      detect=(detect)/nb;
      _valueV=vbat;
      _valueD=detect;
      // Detect..
      skip++;
      if(skip>10)
      {
        skip=0;
        //Logger("DETD=%d ",_valueD);  
        delay(100);
      }
      //;
      _avgDetect[_dex]=_valueD;
      _dex=(_dex+1)%NB_DETECT; // 0.5s
      int ok=0,ko=0;
      for(int i=0;i<NB_DETECT;i++)
      {
          if(_avgDetect[i]>DETECT_THRESHOLD) ok++;
          else ko++;
      }
      if(ko>1)
            _detected=false;
      else
            _detected=true;      
  }    
}
// EOF
