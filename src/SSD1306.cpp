// 
//

#define HWIRE I2C1

#include <Wire.h>
#include "adc/simpleADC.h"
#include "OLED_I2C.h"
#include "MapleFreeRTOS1000_pp.h"
#include "pinMapping.h"
#include "printf.h"
#include "dso_debug.h"
#include "screen.h"

extern "C" unsigned char MediumNumbers[];
extern "C" unsigned char SmallFont[];
extern "C" unsigned char TinyFont[];

class Screen1306 : public MyScreen
{
public:
        Screen1306()
        {
            myOLED=new  OLED(SCREEN_DATA, SCREEN_SCL, SCREEN_RESET);
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
        OLED  *myOLED;
};

MyScreen *createScreen()
{
    return new Screen1306;
}