/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#pragma once
class DSOEeprom
{
public:
        static bool readPulse(int &p);
        static bool writePulse(int p);
        static bool readVoltageOffset(int &p);
        static bool writeVoltageOffset(int p);
        
        static bool format(); 
};