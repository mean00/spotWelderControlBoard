


#include "measurement.h"
#include "dso_debug.h"
#define DETECT_THRESHOLD 1000
/**
 * 
 * @param pinV
 * @param pinD
 */
Measurement::Measurement(int pinV,int pinD) : xTask("MEASURE",  4, 300)
{

  pinMode(pinV,INPUT_ANALOG);
  pinMode(pinD,INPUT_ANALOG);
  _adc=new simpleAdc(pinV);
  int pins[2]={pinV,pinD};
  _adc->setPins(2,pins);
  _vcc=_adc->getVcc();  
  for(int i=0;i<NB_DETECT;i++)  _avgDetect[i]=0;
  _dex=0;
  _detected=false;
}
/**
 * 
 */
int skip=0;
void Measurement::run()
{
  while(1)
  {   
      int nb=64;
      uint16_t *data;
      _adc->timeSample(nb, &data,400); //160ms
      int vbat=0, detect=0;
      
      for(int i=0;i<nb/2;i++)
      {
          vbat+=data[0];
          detect+=data[1];
          data+=2;
      }
      vbat=(vbat*2)/nb;
      detect=(detect*2)/nb;
      _valueV=vbat;
      _valueD=detect;
      // Detect..
      skip++;
      if(skip>10)
      {
        skip=0;
        Logger("DETD=%d",_valueD);  
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
