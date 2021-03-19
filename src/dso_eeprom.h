/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#pragma once
class DSOEeprom
{
public:
        static bool read(int &p);
        static bool write(int p);
        static bool format(); 
};