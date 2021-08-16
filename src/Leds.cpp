
#include "lnArduino.h"
#include "lnSPI.h"
#include "libraries/WS2812B/lnWS2812B.h"
#include "Leds.h"

#define WW ((WS2812B *)_ws)
/**
 * 
 */
WelderLeds::WelderLeds()
{
    _enabled=true;
    _armed=false;
    _voltageDetect=false;
    
    hwlnSPIClass *spi=new hwlnSPIClass(0);
    
    WS2812B *w=new WS2812B(3,spi);
    _ws=(void *)w;
    w->begin();    
    w->setGlobalBrightness(127);
//----    
#define ZZ(x,y,z)        w->setLedColor(0,255*x,0,0); \
    w->setLedColor(1,0,255*y,0); \
    w->setLedColor(2,0,0,255*z); \
    w->update(); \
    delay(100);
//----
    ZZ(1,1,1);
    ZZ(0,0,0);
    ZZ(1,1,1);

    ZZ(1,0,0);
    ZZ(0,1,0);
    ZZ(0,0,1);
    ZZ(0,0,0);
}
/**
 * 
 * @param onoff
 */
void    WelderLeds::setProbeDetectState(bool onoff)
{
    _voltageDetect=onoff;
    update();
}
/**
 * 
 * @param onoff
 */
void    WelderLeds::setArmState(bool onoff)
{
    _armed=onoff;
    update();
}
/**
 * 
 * @param onoff
 */
void    WelderLeds::setEnable(bool onoff)
{
    _enabled=onoff;
    update();
}
/**
 * 
 */
void WelderLeds::single(bool value, int dex, int r, int g , int b)
{
    WS2812B *w=WW;
    if(value) 
        w->setLedColor(dex,r,g,b);
    else 
        w->setLedColor(dex,0,0,0);
        
}
/**
 * 
 */
#define MK(x,y,z) x*255,y*255,z*255

void    WelderLeds::update(void)
{
    WS2812B *w=WW;
    if(!_enabled)
    {
        w->setLedColor(0,0,0,0);
        w->setLedColor(1,0,0,0);
        w->setLedColor(2,0,0,0);
        w->update();
        return;
    }
    single(_voltageDetect,0,MK(1,0,0)) ;
    single(_armed,1,MK(0,1,0)) ;
    w->update();
}
      
