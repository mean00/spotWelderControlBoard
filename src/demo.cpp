// 
//

#define HWIRE I2C1

#include <Wire.h>
#include "adc/simpleADC.h"
#include "OLED_I2C.h"
#include "MapleFreeRTOS1000_pp.h"
#include "rotary.h"
#include "pinMapping.h"
#include "printf.h"
#include "dso_debug.h"
#include "dso_eeprom.h"
#include "measurement.h"

extern void pulseDemo();

void MainTask( void *a );

#define DSO_MAIN_TASK_PRIORITY 10


OLED  *myOLED;
simpleAdc *adc;
Rotary *rotary;
uint8_t ucHeap[configTOTAL_HEAP_SIZE];
extern "C" unsigned char MediumNumbers[];
int pulseWidth=5;



void setup()
{
  
  afio_cfg_debug_ports( AFIO_DEBUG_SW_ONLY); // Unlock PB3 & PB4
  Serial.end();
  //Serial1.begin(115200);  //Wire.begin();
  //Serial.end();
  //Serial1.begin(115200);  
  
  // shutdown usb & spi
  rcc_clk_disable(RCC_SPI1);
  rcc_clk_disable(RCC_SPI2);
  rcc_clk_disable(RCC_USB);
  
  
  //
  
  xTaskCreate( MainTask, "MainTask", 350, NULL, DSO_MAIN_TASK_PRIORITY, NULL );   
  vTaskStartScheduler();      
}

void loop()
{

}
int value=0;
/**
 * 
 * @param 
 */
void MainTask(void *)
{
  LoggerInit();
  Logger("Initializing eeprom\n");
  if(!DSOEeprom::read(pulseWidth))
  {
    Logger("Formating eeprom\n");    
    pulseWidth=5;
    DSOEeprom::format();
    DSOEeprom::write(pulseWidth);
  }  
  
  Measurement measure(PIN_VBAT,PIN_DETECT);
  
  digitalWrite(PIN_GATE,0);
  pinMode(PIN_GATE,OUTPUT);
  
  rotary=new Rotary(ROTARY_LEFT,ROTARY_RIGHT,ROTARY_PUSH);
  rotary->setup();
  
  myOLED=new  OLED(SCREEN_DATA, SCREEN_SCL, SCREEN_RESET);
  myOLED->begin();
  myOLED->setFont(MediumNumbers);    
  myOLED->update();
  
  Logger("Go !\n");
  myOLED->clrScr();
  myOLED->print("GO", 20, 3);  
  myOLED->update();
    //  pulseDemo();
  float vcc=measure.vcc();
  while(1)
  {
   
      int inc=rotary->getRotaryValue();
      value+=inc;
      
      int vbat=measure.getPinV();
      int detect=measure.getPinD();;
      
      float f=vbat;
      f=f*vcc*5.7;
      f+=4200;
      int raw=(int)(f/100.);
      
      myOLED->clrScr();
      myOLED->printNumI(raw, 0, 20, 3);  
      myOLED->printNumI(value, 0, 40, 3);  
      myOLED->printNumI(detect, 80, 20, 3);  
      myOLED->update();
      xDelay(100);
  }
  
}

