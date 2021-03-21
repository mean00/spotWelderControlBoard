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
#include "oled/fonts/Fonts/FreeSansBold9pt7b.h"
#include "oled/fonts/Fonts/FreeSansBold24pt7b.h"


extern "C" unsigned char MediumNumbers[];
extern "C" unsigned char SmallFont[];
extern "C" unsigned char TinyFont[];
extern "C" unsigned char BigNumbers[];


class Screen1306 : public MyScreen
{
public:
        Screen1306()
        {            
#if 0
           SoftWire *sw=new SoftWire(SCREEN_SCL,SCREEN_DATA);
           // pinMode(SCREEN_SCL, OUTPUT);
            myWire=sw;
#else
            // Bug somwhere when using hw i2c
            // need to init it first as sw, then switch to hw
            // missing pinmode ?
            SoftWire *sw=new SoftWire(SCREEN_SCL,SCREEN_DATA);
            sw->begin();
            sw->end();
            delete sw;
            TwoWire *tw=new TwoWire(1,0,400*1000);
            myWire=tw;
#endif            
            
            
            
            myWire->begin();
            myOLED=new  OLED_stm32duino(*myWire, SCREEN_RESET);
            myOLED->setFontFamily(&FreeSansBold9pt7b,&FreeSansBold24pt7b,&FreeSansBold24pt7b);            
            myOLED->setFontSize(OLEDCore::MediumFont); //MediumFont); BigFont
            myOLED->begin();
            int counter=0;
            while(1)
            {
                counter++;
                counter%=25;
                char c='A'+counter;
                myOLED->clrScr();
                myOLED->print(1,48,"12.2");
                myOLED->update();
                xDelay(100);
            }
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
            //myOLED->print(st,x,y);
        }
        virtual void printBigNumber(const char *t, int x, int y)
        {
            
         //   myOLED->setFont(BigNumbers);    
           // myOLED->print(t,x,y);
            //myOLED->setFont(SmallFont);    
        }
        virtual      ~Screen1306() {}
protected:        
        OLED_stm32duino  *myOLED;
        WireBase         *myWire;
};

MyScreen *createScreen()
{
    return new Screen1306;
}
