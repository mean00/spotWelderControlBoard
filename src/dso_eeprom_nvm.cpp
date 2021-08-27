/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#include "lnArduino.h"
#include "dso_eeprom.h"
#include "nvm_gd32.h"

static lnNvmGd32 *nvm=NULL;

#define PULSE_INDEX     1
#define VOLTAGE_INDEX   2
#define TRIGGER_INDEX   3
/**
 */
bool DSOEeprom::init()
{
    nvm=new lnNvmGd32;
    return nvm->begin();
}

/**
 * 
 * @return 
 */
bool DSOEeprom::readPulse(int &pulse)
{
     return readVal(PULSE_INDEX,pulse);  
}

/**
 * 
 * @return 
 */
bool DSOEeprom::readVoltageOffset(int &offset)
{
   return readVal(VOLTAGE_INDEX,offset);  
}

/**
 * 
 * @return 
 */
bool DSOEeprom::readTriggerSource(int &offset)
{
    return readVal(TRIGGER_INDEX,offset);  
}
/**
 * 
 * @return 
 */
bool  DSOEeprom::writePulse(int pulse)
{
     return writeVal(PULSE_INDEX,pulse);
}


/**
 * 
 * @return 
 */
bool  DSOEeprom::writeVoltageOffset(int pulse)
{
      return writeVal(VOLTAGE_INDEX,pulse);
}

/**
 * 
 * @return 
 */
bool  DSOEeprom::writeTriggerSource(int pulse)
{
   return writeVal(TRIGGER_INDEX,pulse);
}


/**
 * 
 * @return 
 */
bool  DSOEeprom::writeVal(int index, int pulse)
{
    return nvm->write(index,4,(uint8_t *)&pulse);
}
/**
 * 
 * @return 
 */
bool DSOEeprom::readVal(int index, int &offset)
{
    return nvm->read(index,4,(uint8_t *)&offset);
}

/**
 */
bool  DSOEeprom::format()
{
    return nvm->format();
}
//
