


#include "measurement.h"

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
}
/**
 * 
 */
void Measurement::run()
{
  while(1)
  {   
      int nb=64;
      uint16_t *data;
      _adc->timeSample(nb, &data,100);
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
  }    
}
// EOF
