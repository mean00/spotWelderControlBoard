// 
//

#define HWIRE I2C1

#include "lnArduino.h"
#include "ssd1306_i2c_lnGd32vf103.h"
#include "pinMapping.h"
#include "screen.h"


extern const GFXfont *getFont(int index);

extern float getCurrentVbat();
extern "C" unsigned char MediumNumbers[];
extern "C" unsigned char SmallFont[];
extern "C" unsigned char TinyFont[];
extern "C" unsigned char BigNumbers[];

/**
 * 
 */
#define SPEED (400*1000)
class Screen1306 : public MyScreen
{
public:
        Screen1306()
        {            
            lnI2C *i2c=new lnI2C(0,SPEED);
            i2c->begin(0x3c);
            myOLED=new OLED_lnGd32( *i2c, -1);
            myOLED->setFontFamily(getFont(0),getFont(1),getFont(2));            
            myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
            myOLED->begin();     
            
        }
        void redrawStockScreen(Welder::Selection sel,  Welder::TriggerSource triggerType, int durationMs,bool contact);
        void redrawArmScreen( int count,  Welder::TriggerSource triggerType, int durationMs);
        virtual void invertText(bool t)
        {
            myOLED->invertText(t);
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
        void setText(int dex, const char *txt, bool inverted);
        void setSelection(int dex);
        void myRoundSquare(int x, int y, int w, int h);
protected:        
        OLEDCore         *myOLED;
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
#define TEXTHEIGHT 18
#define TEXTOFFSET 4
#define TEXTBORDER 1
#define BORDEROFFSET 8


const int yOffset[3]={  BORDEROFFSET+1,
                    TEXTHEIGHT*1-TEXTBORDER+BORDEROFFSET,
                    TEXTHEIGHT*2-TEXTBORDER+BORDEROFFSET-1    
};

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
void Screen1306::setText(int dex, const char *txt, bool inverted)
{
    myOLED->invertText(inverted);
    myOLED->print(60,TEXTOFFSET+TEXTHEIGHT*dex+TEXTHEIGHT,txt);
    myOLED->invertText(false);
}
/**
 * 
 * @param dex
 */
#define RIGHT_SIDE 68

void Screen1306::setSelection(int dex)
{
     myRoundSquare(       128-RIGHT_SIDE-2,
                          //TEXTHEIGHT*dex-TEXTBORDER+BORDEROFFSET,
                          yOffset[dex],
                          66,
                          TEXTHEIGHT+2*TEXTBORDER-2
                          );
}
/**
 * 
 * @param sel
 * @param voltage
 * @param triggerType
 * @param durationMs
 */

void Screen1306::redrawStockScreen(Welder::Selection sel,  Welder::TriggerSource triggerType, int durationMs,bool contact)
{
    char st[5];
    sprintf(st,"%02d",durationMs);
    myOLED->clrScr();
        
    myOLED->setFontSize(OLEDCore::MediumFont); //MediumFont); BigFont
    
    if(contact)
        myOLED->invertText(true);
    myOLED->print(1,40,st);
    myOLED->invertText(false);
    
    
    myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
    sprintf(st,"%02.1fV",getCurrentVbat());
    myOLED->print(2,TEXTOFFSET+TEXTHEIGHT*2+TEXTHEIGHT+1,st);    
    const char *lb;    
    switch(triggerType)
    {
        case Welder::Auto: lb="Auto";break;
        case Welder::Pedal: lb="Pedal";break;
    }
    
#if 0  
    setText(0,"GO!",sel==Welder::GO);    
    setText(1,lb,sel==Welder::Trigger);    
    setText(2,"Settng",sel==Welder::Settings);
    
#else
    
    setText(0,"GO!",false);
    setText(1,lb,false);    
    setText(2,"Settng",false);
    
    switch(sel)
    {
        case   Welder::Duration:     
                                    myRoundSquare(0,  12,
                                                  56, 32);
                                    break;
        case   Welder::Trigger:     setSelection(1);break;
        case   Welder::Settings:    setSelection(2);break;
        case   Welder::GO:          setSelection(0);break;            
        default: xAssert(0);break;
    }
#endif

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
    myOLED->print(RIGHT_SIDE,32,st);
    
    myOLED->setFontSize(OLEDCore::SmallFont); //MediumFont); BigFont
    const char *lb;    
    switch(triggerType)
    {
        case Welder::Auto: lb="Auto";break;
        case Welder::Pedal: lb="Pedal";break;
    }
    myOLED->print(RIGHT_SIDE,48,lb);
    
    sprintf(st,"%02.1fv",getCurrentVbat());
    myOLED->print(RIGHT_SIDE,64,st);    
}



// EOF
