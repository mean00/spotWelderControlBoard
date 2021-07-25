// 
//
//

#include "lnArduino.h"
#include "libraries/RotaryEncoder/RotaryEncoder.h"
#include "pinMapping.h"
#include "lnArduino.h"
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
#include "Leds.h"

extern void pulseDemo();

extern Navigate * spawnMainMenu(void);
#define DSO_MAIN_TASK_PRIORITY 10
extern void bench();

MyScreen *myScreen;
lnSimpleADC *adc;
lnRotary *rotary;
Pedal *myPedal;
WelderLeds *myLeds;

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
  digitalWrite(PIN_GATE,0);
  lnPinMode(PIN_GATE,lnOUTPUT);   
}

/**
 * 
 * @param 
 */
void loop()
{  
  digitalWrite(PIN_GATE,0);
  lnPinMode(PIN_GATE,lnOUTPUT);   
  
  Logger("Initializing screen\n");
    
  myScreen=createScreen();
    
  //bench();
  
  myScreen->clear();
  myScreen->rleDisplay(splash_width, splash_height, 2 , 6, splash);
  
  myScreen->print("Spot",70,20);
  myScreen->print("Weldr",70,40);
  myScreen->print(WELDER_VERSION,70,60);
  myScreen->update();
  
  Logger("Splash\n");
    
    
   // turn off gate asap
  Logger("Initializing eeprom\n");
  
  
  myLeds=new WelderLeds();
  
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
  
  Logger("Initializing Pedal\n");
  myPedal=new Pedal(PIN_PEDAL);
  
  Logger("Initializing Rotary\n");
  rotary=new lnRotary(ROTARY_PUSH, ROTARY_LEFT,ROTARY_RIGHT);
  rotary->start();
   
  Logger("Wait\n");
  xDelay(1000);
  
  Navigate *currentMenu= spawnMainMenu();
  Logger("Entering loop\n");
  while(1)
  {
      bool dirty=false;
      lnRotary::EVENTS ev=rotary->readEvent();
      if(ev & lnRotary::ROTARY_CHANGE)
      {
        int inc=rotary->getCount();
        if(inc)
        {
              currentMenu->handleRotary(inc);
              dirty=true;
        }
      }
      if(!dirty)
      {
          Navigate::Event event;
          bool subMenu=false;          
          Navigate *z;
          if(ev & lnRotary::SHORT_PRESS)
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
               rotary->readEvent();                   
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
    static bool oldConnect=false;
    bool s= measure->detected();
    if(s!=oldConnect)
    {
        oldConnect=s;
        myLeds->setProbeDetectState(s);
    }
    return s;
}