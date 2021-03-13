// OLED_I2C_3D_Cube
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my OLED_I2C library to rotate a 3D cube.
// The average FPS (Frames Per Second) will be displayed on the screen.
//
// NOTE: The FPS counter will overflow if left for an extended amount of time.
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the OLED display to any available pin but if you use 
// any other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

#define HWIRE I2C1

#include <Wire.h>
#include "adc/simpleADC.h"
#include "OLED_I2C.h"
#include "MapleFreeRTOS1000_pp.h"


void MainTask( void *a );

#define DSO_MAIN_TASK_PRIORITY 10

#define PIN_VBAT   PA1
#define PIN_DETECT PA2
#define PIN_GATE   PA3


OLED  *myOLED;
simpleAdc *adc;
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

void MainTask(void *)
{
  pinMode(PIN_VBAT,INPUT_ANALOG);
  pinMode(PIN_DETECT,INPUT_ANALOG);
  digitalWrite(PIN_GATE,0);
  pinMode(PIN_GATE,OUTPUT);
  
  myOLED=new  OLED(PB7, PB6, PB5);
  myOLED->begin();
  myOLED->setFont(MediumNumbers);    
  myOLED->update();
  adc=new simpleAdc(PA1);
  int pins[2]={PIN_VBAT,PIN_DETECT};
  adc->setPins(2,pins);
  
  while(1)
  {
      int nb=16;
      uint16_t *data;
      adc->timeSample(nb, &data,1000);
      int vbat=0, detect=0;
      
      for(int i=0;i<nb/2;i++)
      {
          vbat+=data[0];
          detect+=data[1];
          data+=2;
      }
      vbat=(vbat*2)/nb;
      detect=(detect*2)/nb;
      
        myOLED->clrScr();
        myOLED->printNumI(vbat, 0, 0, 3);  
        myOLED->printNumI(detect, 0, 30, 3);  
        myOLED->update();
  }
  
}

