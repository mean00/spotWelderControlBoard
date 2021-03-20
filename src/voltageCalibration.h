
#pragma once
#include "navigate.h"

/**
 * 
 * @param p
 */
class Calibration : public Navigate
{
public:
   
            Calibration(Navigate *p);                
    virtual ~Calibration();
    virtual Navigate *handleEvent(Event evt,bool &subMenu);
    virtual void redraw();
    virtual void  handleRotary(int inc);

protected:
    int     voltageCalibration;    
};