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
//#include "oled/fonts/Fonts/FreeSansBold9pt7b.h"
#include "oled/fonts/Fonts/FreeSans9pt7b.h"
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
#if 1
            // Bug somwhere when using hw i2c
            // need to init it first as sw, then switch to hw
            // missing pinmode ?
            SoftWire *sw=new SoftWire(SCREEN_SCL,SCREEN_DATA);
            sw->begin();
            sw->end();
            delete sw;
#endif            
            TwoWire *tw=new TwoWire(1,0,400*1000);
            myWire=tw;
#endif            
            
            
            
            myWire->begin();
            myOLED=new  OLED_stm32duino(*myWire, SCREEN_RESET);
            myOLED->setFontFamily(&FreeSans9pt7b,&FreeSansBold24pt7b,&FreeSansBold24pt7b);            
            myOLED->setFontSize(OLEDCore::MediumFont); //MediumFont); BigFont
            myOLED->begin();     
            
        }
        void redrawStockScreen(Welder::Selection sel, float voltage, Welder::TriggerType triggerType, int durationMs);
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
             myOLED->print(x,y,st);
        }
        virtual void printBig(const char *t, int x, int y)
        {
             myOLED->setFontSize(OLEDCore::MediumFont); 
             myOLED->print(x,y,t);
             myOLED->setFontSize(OLEDCore::SmallFont); 
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

#define SEL(x) if(sel==Welder::x) myOLED->invertText(true);
#define ENDSEL() myOLED->invertText(false);

/**
 * 
 * @param sel
 * @param voltage
 * @param triggerType
 * @param durationMs
 */
void Screen1306::redrawStockScreen(Welder::Selection sel, float voltage, Welder::TriggerType triggerType, int durationMs)
{
    char st[5];
    sprintf(st,"%02d",durationMs);
    myOLED->clrScr();
    myOLED->setFontSize(OLEDCore::MediumFont); //MediumFont); BigFont
    
    SEL( Duration);    
    myOLED->print(1,40,st);
    ENDSEL();

    myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
    sprintf(st,"%02.1fV",voltage);
    myOLED->print(2,63,st);    
    const char *lb;    
    switch(triggerType)
    {
        case Welder::Auto: lb="Manual";break;
        case Welder::Pedal: lb="Pedal";break;
    }
    SEL( Trigger);
    myOLED->print(60,30,lb);
    ENDSEL();
    SEL( Settings);    
    myOLED->print(60,60,"Setting");
    ENDSEL();
    myOLED->update();
    xDelay(100);
    
}