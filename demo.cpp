// 
//

#define HWIRE I2C1

#include <Wire.h>
#include "adc/simpleADC.h"
#include "OLED_I2C.h"
#include "MapleFreeRTOS1000_pp.h"
#include "rotary.h"
#include "pinMapping.h"
void MainTask( void *a );

#define DSO_MAIN_TASK_PRIORITY 10


OLED  *myOLED;
simpleAdc *adc;
Rotary *rotary;
uint8_t ucHeap[configTOTAL_HEAP_SIZE];


extern uint8_t MediumNumbers[];

void setup()
{
  
  afio_cfg_debug_ports( AFIO_DEBUG_SW_ONLY); // Unlock PB3 & PB4
  Serial.end();
  //Serial1.begin(115200);  //Wire.begin();
  //Serial.end();
  //Serial1.begin(115200);  
  xTaskCreate( MainTask, "MainTask", 350, NULL, DSO_MAIN_TASK_PRIORITY, NULL );   
  vTaskStartScheduler();      
}

void loop()
{

}
int value=0;
void MainTask(void *)
{
  pinMode(PIN_VBAT,INPUT_ANALOG);
  pinMode(PIN_DETECT,INPUT_ANALOG);
  digitalWrite(PIN_GATE,0);
  pinMode(PIN_GATE,OUTPUT);
  
  rotary=new Rotary(ROTARY_LEFT,ROTARY_RIGHT,ROTARY_PUSH);
  rotary->setup();
  
  myOLED=new  OLED(SCREEN_DATA, SCREEN_SCL, SCREEN_RESET);
  myOLED->begin();
  myOLED->setFont(MediumNumbers);    
  myOLED->update();
  adc=new simpleAdc(PA1);
  int pins[2]={PIN_VBAT,PIN_DETECT};
  adc->setPins(2,pins);
  float vcc=adc->getVcc();
  vcc=vcc/4095.;
  while(1)
  {
   
      int inc=rotary->getRotaryValue();
      value+=inc;
      
      int nb=64;
      uint16_t *data;
      adc->timeSample(nb, &data,100);
      int vbat=0, detect=0;
      
      for(int i=0;i<nb/2;i++)
      {
          vbat+=data[0];
          detect+=data[1];
          data+=2;
      }

      float f=vbat;
      f=f*vcc*5.7;
      f=(f*2.)/nb;
      f+=4200;
      int raw=(int)(f/100.);
      
      myOLED->printNumI(raw, 0, 20, 3);  
      myOLED->printNumI(value, 0, 40, 3);  
      myOLED->update();
      xDelay(100);
  }
  
}

