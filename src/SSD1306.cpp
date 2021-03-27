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

extern float getCurrentVbat();
extern "C" unsigned char MediumNumbers[];
extern "C" unsigned char SmallFont[];
extern "C" unsigned char TinyFont[];
extern "C" unsigned char BigNumbers[];

/**
 * 
 */
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
            myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
            myOLED->begin();     
            
        }
        void redrawStockScreen(Welder::Selection sel,  Welder::TriggerSource triggerType, int durationMs);
        void redrawArmScreen( int count,  Welder::TriggerSource triggerType, int durationMs);
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
        virtual void disconnectMessage()
        {
             myOLED->clrScr();
             print("Move pins!", 2,32+10);
             myOLED->update();
        }
        virtual void rleDisplay(int width, int height,int at_x, int at_y, const uint8_t *data)
        {
            myOLED->drawRLEBitmap(width,height, at_x,at_y,1,0,data);
        }
        virtual      ~Screen1306() {}
protected:
        void setText(int dex, const char *txt);
        void setSelection(int dex);
        void myRoundSquare(int x, int y, int w, int h);
protected:        
        OLED_stm32duino  *myOLED;
        WireBase         *myWire;
};
/**
 * 
 * @return 
 */
MyScreen *createScreen()
{
    return new Screen1306;
}


/**
 * 
 * @param sel
 * @param voltage
 * @param triggerType
 * @param durationMs
 */
#define TEXTHEIGHT 19
#define TEXTOFFSET 3
#define TEXTBORDER 1
#define BORDEROFFSET 8
/**
 * 
 * @param x
 * @param y
 * @param w
 * @param h
 */
void Screen1306::myRoundSquare(int x, int y, int w, int h)
{
    int y1=64-y;
    int y2=64-(y+h);
    int x2=x+w;
     myOLED->drawRoundRect(x,y1,x2,y2);
}
/**
 * 
 * @param dex
 * @param txt
 */
void Screen1306::setText(int dex, const char *txt)
{
     myOLED->print(60,TEXTOFFSET+TEXTHEIGHT*dex+TEXTHEIGHT,txt);
}
/**
 * 
 * @param dex
 */
void Screen1306::setSelection(int dex)
{
     myRoundSquare(58,TEXTHEIGHT*dex-TEXTBORDER+BORDEROFFSET,
                          62,TEXTHEIGHT+2*TEXTBORDER-1
                          );
}
/**
 * 
 * @param sel
 * @param voltage
 * @param triggerType
 * @param durationMs
 */
void Screen1306::redrawStockScreen(Welder::Selection sel,  Welder::TriggerSource triggerType, int durationMs)
{
    char st[5];
    sprintf(st,"%02d",durationMs);
    myOLED->clrScr();
    myOLED->setFontSize(OLEDCore::MediumFont); //MediumFont); BigFont
    
    myOLED->print(1,40,st);
    
    myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
    sprintf(st,"%02.1fV",getCurrentVbat());
    myOLED->print(2,63,st);    
    const char *lb;    
    switch(triggerType)
    {
        case Welder::Auto: lb="Manual";break;
        case Welder::Pedal: lb="Pedal";break;
    }
    setText(0,"GO!");
    setText(1,lb);
    setText(2,"Setting");

    switch(sel)
    {
        case   Welder::Duration:     
                myRoundSquare(2,2,56,46);
                break;
        case   Welder::Trigger:     setSelection(1);break;
        case   Welder::Settings:    setSelection(2);break;
        case   Welder::GO:          setSelection(0);break;            
        default: xAssert(0);break;
    }


    myOLED->update();
}
/**
 * 
 * @param voltage
 * @param triggerType
 * @param durationMs
 */
void Screen1306::redrawArmScreen( int count, Welder::TriggerSource triggerType, int durationMs)
{
    char st[5];

    myOLED->clrScr();
    
    myOLED->setFontSize(OLEDCore::MediumFont); //MediumFont); BigFont
    
    if(count>=0)
    {
        sprintf(st,"%02d",count);  
        myOLED->invertText(true);
        myOLED->print(1,40,st);
        myOLED->invertText(false);
    }
    sprintf(st,"%02d",durationMs);
    myOLED->print(64,40,st);
    
    myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
    const char *lb;    
    switch(triggerType)
    {
        case Welder::Auto: lb="Manual";break;
        case Welder::Pedal: lb="Pedal";break;
    }
    myOLED->print(64,48,lb);
    
    sprintf(st,"%02.1fV",getCurrentVbat());
    myOLED->print(64,64,st);    
}



// EOF