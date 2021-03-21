/**
 * This is the stm32duino bluepill specific implentation
 * @param wire
 * @param reset
 */

#include "ssd1306_i2c_f1.h"
#include "ssd1306_cmd.h"
/**
 * 
 * @param wire
 * @param reset
 */
OLED_stm32duino::OLED_stm32duino(WireBase &wire, int reset) : OLEDCore(reset),_wire(wire)
{
    
}
/**
 * 
 * @param cmd
 */
void    OLED_stm32duino::sendCommand(uint8_t cmd)
{    
    _wire.beginTransmission(SSD1306_ADDR);
    _wire.write(SSD1306_COMMAND);
    _wire.write(cmd);
    _wire.endTransmission();    
}

/**
 * 
 * @param cmd
 */
const uint8_t beginHeader[]={
    SSD1306_COMMAND,SSD1306_SET_COLUMN_ADDR,0,127,SSD1306_SET_PAGE_ADDR,0,7,SSD1306_DATA
};
void    OLED_stm32duino::beginData()
{    
    _wire.beginTransmission(SSD1306_ADDR);
    _wire.write((uint8_t *)beginHeader,sizeof(beginHeader));
    _wire.endTransmission();   
}
/**
 * 
 */
void    OLED_stm32duino::update()
{
    beginData();
 #define CHUNK 16      
    for (int b=0; b<1024; b+=CHUNK)		// Send data
    {
     _wire.beginTransmission(SSD1306_ADDR);
     _wire.write(SSD1306_DATA_CONTINUE);
     _wire.write(scrbuf+b,CHUNK);
     _wire.endTransmission();
    }
    
}

