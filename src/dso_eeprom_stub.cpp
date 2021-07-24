/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#include "lnArduino.h"
#include "dso_eeprom.h"
/**
 * 
 * @return 
 */
bool DSOEeprom::readPulse(int &pulse)
{
    pulse=20;
    return true;
}
/**
 * 
 * @return 
 */
bool  DSOEeprom::writePulse(int pulse)
{
    return true;
}

/**
 * 
 * @return 
 */
bool DSOEeprom::readVoltageOffset(int &offset)
{
    offset=0;
    return true;
}


/**
 * 
 * @return 
 */
bool  DSOEeprom::writeVoltageOffset(int pulse)
{
    return true;
}
//--

/**
 * 
 * @return 
 */
bool DSOEeprom::readTriggerSource(int &offset)
{
    offset=0;
    return true;
}


/**
 * 
 * @return 
 */
bool  DSOEeprom::writeTriggerSource(int pulse)
{
    return true;
}


/**
 * 
 * @return 
 */
bool  DSOEeprom::writeVal(int index, int pulse)
{
        
    return true;
}
/**
 * 
 * @return 
 */
bool DSOEeprom::readVal(int index, int &offset)
{
    offset=0;
    return true;
}

/**
 */
bool  DSOEeprom::format()
{
    return true;
}
//
