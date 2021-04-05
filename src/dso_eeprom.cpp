/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#include "EEPROM.h"
#include "dso_eeprom.h"

static uint16_t calibrationHash=0;
static uint16_t pulseWidth=5;
#define CURRENT_HASH     0x1234
#if 0
    #define CHECK_READ(x) xAssert(x)
#else
    #define CHECK_READ(x) if(!(x)) return false;
#endif

#define PULSE_INDEX     1
#define VOLTAGE_INDEX   2
#define TRIGGER_INDEX   3

/**
 * 
 * @return 
 */
extern void *eeprom_begin;
static void addressInit(EEPROMClass &e2)
{
    uint32 pageBase0=(uint32_t)&eeprom_begin;    
    e2.init(pageBase0,pageBase0+2*1024,2*1024);
}
/**
 * 
 * @return 
 */
bool DSOEeprom::readPulse(int &pulse)
{
    EEPROMClass e2;
    addressInit(e2);
    calibrationHash=e2.read(0);
    if(calibrationHash!=CURRENT_HASH)
    {
        return false;
    }
    return readVal(PULSE_INDEX,pulse);  
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
bool DSOEeprom::readVoltageOffset(int &offset)
{
    return readVal(VOLTAGE_INDEX,offset);    
}


/**
 * 
 * @return 
 */
bool  DSOEeprom::writeVoltageOffset(int pulse)
{
    return writeVal(VOLTAGE_INDEX,pulse);
}
//--

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
    EEPROMClass e2;
    addressInit(e2);
    uint16_t p16=pulse;
    e2.update(index,p16);
    
    return true;
}
/**
 * 
 * @return 
 */
bool DSOEeprom::readVal(int index, int &offset)
{
    EEPROMClass e2;
    addressInit(e2);
    calibrationHash=e2.read(0);
    if(calibrationHash!=CURRENT_HASH)
    {
        return false;
    }
    uint16_t po;
    if(EEPROM_OK==e2.read(index,&po))
    {
        offset=po;
        return true;
    }
    return false;
}

/**
 */
bool  DSOEeprom::format()
{
    EEPROMClass e2;
    addressInit(e2);
    e2.format();
    e2.write(0,CURRENT_HASH);
    e2.write(PULSE_INDEX,5);
    return true;
}
//