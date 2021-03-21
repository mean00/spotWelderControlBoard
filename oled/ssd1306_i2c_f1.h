#include "Wire.h"
#include "ssd1306_i2c.h"

class OLED_stm32duino : public  OLEDCore
{
    public:
                OLED_stm32duino(WireBase &wire, int reset);
        void    sendCommand(uint8_t cmd);
        void    update();
        //--
        void    beginData();
    protected:
        WireBase &_wire;
    
};


