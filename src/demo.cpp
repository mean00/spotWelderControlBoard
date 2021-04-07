// 
//
//

#include <Wire.h>
#include "adc/simpleADC.h"
#include "MapleFreeRTOS1000_pp.h"
#include "rotary.h"
#include "pinMapping.h"
#include "printf.h"
#include "dso_debug.h"
#include "dso_eeprom.h"
#include "measurement.h"
#include "navigate.h"
#include "voltageCalibration.h"
#include "screen.h"
#include "buzzer.h"
#include "trigger.h"
#include "assets.h"
#include "welderVersion.h"
#include "pedal.h"
extern void pulseDemo();

void MainTask( void *a );
extern Navigate * spawnMainMenu(void);
#define DSO_MAIN_TASK_PRIORITY 10
extern void bench();

MyScreen *myScreen;
simpleAdc *adc;
Rotary *rotary;
Pedal *myPedal;
uint8_t ucHeap[configTOTAL_HEAP_SIZE];

int pulseWidth=5;
int voltageOffset=1000;
Measurement *measure;
extern Welder::TriggerSource triggerSource;

int getVBat10(int offset);

/**
 * 
 */
void setup()
{
  // turn off gate asap
  digitalWrite(PIN_GATE,0);
  pinMode(PIN_GATE,OUTPUT);  
  afio_cfg_debug_ports( AFIO_DEBUG_SW_ONLY); // Unlock PB3 & PB4
  Serial.end();
  // shutdown usb & spi
  rcc_clk_disable(RCC_SPI1);
  rcc_clk_disable(RCC_SPI2);
  rcc_clk_disable(RCC_USB);
  xTaskCreate( MainTask, "MainTask", 350, NULL, DSO_MAIN_TASK_PRIORITY, NULL );   
  vTaskStartScheduler();      
}

void loop()
{

}
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
    voltageOffset=1000;
    DSOEeprom::format();
    DSOEeprom::writePulse(pulseWidth);
    DSOEeprom::writeVoltageOffset(voltageOffset);
    DSOEeprom::writeTriggerSource(triggerSource);
  }  
  DSOEeprom::readVoltageOffset(voltageOffset);
  int ts=(int)triggerSource;
  DSOEeprom::readTriggerSource(ts);
  triggerSource=(Welder::TriggerSource )ts;
  measure=new Measurement(PIN_VBAT,PIN_DETECT);
  
  
  myPedal=new Pedal(PIN_PEDAL);
  
  
  rotary=new Rotary(ROTARY_LEFT,ROTARY_RIGHT,ROTARY_PUSH);
  rotary->setup();
  
  myScreen=createScreen();
  interrupts();
  
  //bench();
  
  myScreen->clear();
  myScreen->rleDisplay(splash_width, splash_height, 2 , 6, splash);
  
  myScreen->print("Spot",70,20);
  myScreen->print("Weldr",70,40);
  myScreen->print(WELDER_VERSION,70,60);
  myScreen->update();
  
  Logger("Splash\n");
  
  xDelay(1000);
  
  Navigate *currentMenu= spawnMainMenu();
  Logger("Entering loop\n");
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
          Navigate::Event event;
          bool subMenu=false;
          bool push=(int)rotary->getPush();
          Navigate *z;
          if(push)
          {
              event=Navigate::E_PUSH;
          }else
          {
              event=Navigate::E_TIMER;
          }
           z=currentMenu->handleEvent(event,subMenu);
           if(z)
           {
               if(subMenu)
               {
                    currentMenu=z;
               }
               else
               {
                   // Go back to parent
                   delete currentMenu; 
                   z->redraw();
               }
               currentMenu=z;
               // Purge pending push button if any
               rotary->getPush();
                   
           }
      }
     xDelay(20);
  }
  

    //  pulseDemo();
  
  
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

float getCurrentVbat()
{
     return (0.5+getVBat10(voltageOffset))/10.;
}
bool detectConnection()
{
    return measure->detected();
}