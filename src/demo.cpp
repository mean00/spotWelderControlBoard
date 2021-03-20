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
#include "navigate.h"
#include "voltageCalibration.h"

extern void pulseDemo();

void MainTask( void *a );
extern Navigate * spawnMainMenu();
#define DSO_MAIN_TASK_PRIORITY 10


OLED  *myOLED;
simpleAdc *adc;
Rotary *rotary;
uint8_t ucHeap[configTOTAL_HEAP_SIZE];
extern "C" unsigned char MediumNumbers[];
extern "C" unsigned char SmallFont[];
extern "C" unsigned char TinyFont[];

int pulseWidth=5;

Measurement *measure;

int getVBat10(int offset);

void setup()
{
  // turn off gate asap
  digitalWrite(PIN_GATE,0);
  pinMode(PIN_GATE,OUTPUT);
  
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
  if(!DSOEeprom::readPulse(pulseWidth))
  {
    Logger("Formating eeprom\n");    
    pulseWidth=5;
    DSOEeprom::format();
    DSOEeprom::writePulse(pulseWidth);
  }  
  
  measure=new Measurement(PIN_VBAT,PIN_DETECT);
  
  rotary=new Rotary(ROTARY_LEFT,ROTARY_RIGHT,ROTARY_PUSH);
  rotary->setup();
  
  myOLED=new  OLED(SCREEN_DATA, SCREEN_SCL, SCREEN_RESET);
  myOLED->begin();
  myOLED->setFont(SmallFont);    
  myOLED->update();
  
  
 // Navigate *currentMenu= spawnMainMenu();
  Navigate *currentMenu=new Calibration(NULL);
  
  while(1)
  {
      bool dirty=false;
      int inc=rotary->getRotaryValue();
      if(inc)
      {
            currentMenu->handleRotary(inc);
            dirty=true;
      }
      if(!dirty)
      {
          bool subMenu=false;
           Navigate *z=currentMenu->handleEvent(Navigate::E_TIMER,subMenu);
           if(z)
           {
               if(subMenu)
               {
                    currentMenu=z;
               }
               else
               {
                   delete currentMenu;                   
               }
               currentMenu=z;
                   
           }
      }
      xDelay(20);
  }
  
  Logger("Go !\n");
  myOLED->clrScr();
  myOLED->print("GO", 20, 3);  
  myOLED->update();
    //  pulseDemo();
  
  while(1)
  {
   
      int inc=rotary->getRotaryValue();
      value+=inc;
      
      int raw=getVBat10(1600);
      
      
      myOLED->clrScr();
      myOLED->printNumI(raw, 0, 20, 3);  
      myOLED->printNumI(value, 0, 40, 3);  
//      myOLED->printNumI(detect, 80, 20, 3);  
      myOLED->update();
      xDelay(100);
  }
  
}
/**
 * 
 * @param offset
 * @return 
 */
int getVBat10(int offset)
{
      int vbat=measure->getPinV();
      
      float f=vbat;
      f=f*measure->vcc()*5.65/4095.;
      f+=offset;
      int raw=(int)((f+49.)/100.);
      return raw;
}