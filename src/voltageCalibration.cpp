
#define HWIRE I2C1

#include <Wire.h>
#include "screen.h"
#include "MapleFreeRTOS1000_pp.h"
#include "pinMapping.h"
#include "printf.h"
#include "dso_debug.h"
#include "dso_eeprom.h"
#include "navigate.h"
#include "vector"
#include "dso_eeprom.h"

#include "voltageCalibration.h"

extern MyScreen *myScreen;




/**
 * 
 * @param p
 */
Calibration::Calibration(Navigate *p): Navigate(p)
{
   
    DSOEeprom::readVoltageOffset(voltageCalibration);
    redraw();
}
/**
 * 
 */
Calibration::~Calibration()
{
   
}
extern int getVBat10(int offset);

/**
 * 
 */
void Calibration::redraw()
{
    float v= getVBat10(voltageCalibration);
    v=v/10.;
    char tmp[16];
    sprintf(tmp,"%02.1f",v);    
    myScreen->clear();
    myScreen->print("Adjust voltage",10,20);        
    myScreen->printBigNumber(tmp,4,40);
    myScreen->update();
}
/**
 * 
 * @param inc
 */
void  Calibration::handleRotary(int inc)
{
    voltageCalibration+=inc*100; // it's in mv, so *100 = 0.1 v increment
    if(voltageCalibration<0) voltageCalibration=0;
    if(voltageCalibration>2000) voltageCalibration=2000;
    redraw();
}

Navigate *Calibration::handleEvent(Event evt,bool &subMenu)
{
    return NULL;
}