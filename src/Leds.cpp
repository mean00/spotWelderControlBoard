
#include "Arduino.h"
#include "WS2812B.h"
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
    WS2812B *w=new WS2812B(3);
    _ws=(void *)w;
    w->begin();
    w->setBrightness(127);
    w->setPixelColor(0,0);
    w->setPixelColor(1,0);
    w->setPixelColor(2,0);
    w->show();
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
void WelderLeds::single(bool value, int dex, uint32_t color)
{
    WS2812B *w=WW;
    if(value) 
        w->setPixelColor(dex,color);
    else 
        w->setPixelColor(dex,0);
        
}
/**
 * 
 */
#define MK(x,y,z) ((x*255)<<16)+((y*255)<<8)+(z*255)

void    WelderLeds::update(void)
{
    WS2812B *w=WW;
    if(!_enabled)
    {
        w->setPixelColor(0,0);
        w->setPixelColor(1,0);
        w->setPixelColor(2,0);
        w->show();
        return;
    }
    single(_voltageDetect,0,MK(1,0,0)) ;
    single(_armed,1,MK(0,1,0)) ;
    w->show();
}
      
