#include "navigate.h"
#include "dso_eeprom.h"
#include "voltageCalibration.h"

extern int voltageOffset;
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
    myScreen->print("Adjust voltage",2,20);        
    myScreen->printBig(tmp,4,60);
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
    switch(evt)
    {
        case Navigate::E_PUSH:
            DSOEeprom::writeVoltageOffset(voltageCalibration);
            voltageOffset=voltageCalibration;
            subMenu=false;
            return _parent;
        case Navigate::E_TIMER:
            redraw();
            return NULL;
        default:
            xAssert(0);
            break;
            
    }
    return NULL;
}

Navigate *spawnCalibration(Navigate *parent)
{
    return new Calibration(parent);
}