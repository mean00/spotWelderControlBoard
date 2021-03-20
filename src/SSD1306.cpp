// 
//

#define HWIRE I2C1

#include "Wire.h"
#include "SoftWire.h"
#include "adc/simpleADC.h"
#include "ssd1306_i2c_f1.h"
#include "MapleFreeRTOS1000_pp.h"
#include "pinMapping.h"
#include "printf.h"
#include "dso_debug.h"
#include "screen.h"

extern "C" unsigned char MediumNumbers[];
extern "C" unsigned char SmallFont[];
extern "C" unsigned char TinyFont[];

#if 0
    TwoWire wire(1,0,10*1000);
    #define WIRE wire
#else
    SoftWire  softwire(SCREEN_SCL,SCREEN_DATA);
    #define WIRE softwire
#endif


class Screen1306 : public MyScreen
{
public:
        Screen1306()
        {            
            pinMode(SCREEN_SCL, OUTPUT);
            WIRE.begin();
            myOLED=new  OLED_stm32duino(WIRE, SCREEN_RESET);
            myOLED->begin();
            myOLED->setFont(SmallFont);    
            myOLED->update();
        }
        virtual void clear()
        {
            myOLED->clrScr();
        }
        virtual void update()
        {
            myOLED->update();
        }
        virtual void print(const char *st, int x, int y)
        {
            myOLED->print(st,x,y);
        }
        virtual void printBigNumber(const char *t, int x, int y)
        {
            
            myOLED->setFont(MediumNumbers);    
            myOLED->print(t,x,y);
            myOLED->setFont(SmallFont);    
        }
        virtual      ~Screen1306() {}
protected:        
        OLED_stm32duino  *myOLED;
};

MyScreen *createScreen()
{
    return new Screen1306;
}