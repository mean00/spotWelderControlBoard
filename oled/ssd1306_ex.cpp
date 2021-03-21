#include "ssd1306_i2c.h"

/**
 * \fn checkFont
 * \brief extract max width/ max height from the font
 */
static void checkFont(const GFXfont *font, OLED::FontInfo *info)
{
    int mW=0,mH=0;
    int x,y;
   for(int i=font->first;i<font->last;i++)
   {
         GFXglyph *glyph  = font->glyph+i-font->first;
         x=glyph->xAdvance;
         y=-glyph->yOffset;
         if(x>mW) mW=x;         
         if(y>mH) mH=y;
   }
    info->maxHeight=mH + 1;
    info->maxWidth=mW;    
    info->font=font;
}



/**
 * 
 * @param small
 * @param medium
 * @param big
 */
void  OLED::setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big)
{
    checkFont(small, fontInfo+0);
    checkFont(medium,fontInfo+1);
    checkFont(big,   fontInfo+2);
}       


// hooks
static GFXglyph *pgm_read_glyph_ptr(const GFXfont *gfxFont, uint8_t c) {  return gfxFont->glyph + c;}
static  uint8_t *pgm_read_bitmap_ptr(const GFXfont *gfxFont) {  return gfxFont->bitmap;}


/**
 * 
 * @param x
 * @param y
 * @param c
 * @param color
 * @param bg
 */
void OLED::myDrawChar(int16_t x, int16_t y, unsigned char c,  bool invert) 
{
    int cr=c;
    cr -= gfxFont->first;
    GFXglyph *glyph =  gfxFont->glyph + cr;
    uint8_t *bitmap = gfxFont->bitmap;

    int bo = glyph->bitmapOffset;
    int w = glyph->width;
    int h = glyph->height;
    x+=glyph->xOffset;
    y+=glyph->yOffset;
   
    #define OFFSET -1
    bool first=true;
    int dex=0;

    int bits = 0, bit = 0;
    int n=h*w;
    int mask=0;
    uint8_t *data=bitmap+bo;
    for(int hh=0;hh<h;hh++)
    {
    for(int ww=0;ww<w;ww++)
    {
        if (!mask) 
        {
          bits = *data++;       
          mask=0x80;
        }
        if (bits & mask) 
        {          
            setPixel(x+ww,y+hh);
        }else
        {
            clrPixel(x+ww,y+hh);
        }
        mask>>=1;
        dex++;
    }
    }
    return;
}

void  OLED::setFontSize(FontSize size)
{
    switch(size)
    {
        case SmallFont :  currentFont=fontInfo+0;break;
        default:
        case MediumFont :   currentFont=fontInfo+1;break;
        case BigFont :   currentFont=fontInfo+2;break;
    }    
    gfxFont=currentFont->font;
}

#if 0
/**
 * 
 * @param widthInPixel
 * @param height
 * @param wx
 * @param wy
 * @param fgcolor
 * @param bgcolor
 * @param data
 */
void OLED::drawRLEBitmap(int widthInPixel, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{    
    uint16_t *line=lineBuffer;
    bool first=true;
    int nbPixel=widthInPixel*height;
    int pixel=0;
    setAddrWindow(wx, wy, wx+widthInPixel-1, wy+height);
    int mask=0;
    int cur;   
    uint16_t *o=line;
    int ready=0;
    int repeat;
    uint16_t color;
    while(pixel<nbPixel)        
    {
        // load next
        cur=*data++;
        if(cur==0x76)
        {
            cur=*data++;
            repeat=*data++;
        }else
        {
            repeat=1;
        }
        // 8 pixels at a time
        for(int r=0;r<repeat;r++)
        {
            int mask=0x80;
            for(int i=0;i<8;i++)
            {
                if(mask & cur)
                {
                    color=fgcolor;
                }else
                    color=0xff00*0+1*bgcolor;
                mask>>=1;
                *o++=color;
                ready++;
            }
            if(ready>(ST7735_BUFFER_SIZE-16))
            { // Flush
              pushColors16(line,ready,first);  
              first=false;
              ready=0;
              o=line;
            }
        }
        pixel+=repeat*8;
    }
    pushColors16(line,ready,true);  
}
 
/**
 * 
 * @param z
 */
void  OLED::print(const char *z)
{
   int l=strlen(z);
   while(*z)
   {
       int inc=write(*z);
       cursor_x+=inc;
       z++;
   }
}
void  OLED::print(float f)
{
    char st[50];
    sprintf(st,"%f",f);
    print(st);
}
   void  OLED::print(int f)
{
    char st[50];
    sprintf(st,"%d",f);
    print(st);
}     
/**
 * 
 * @param c
 * @return 
 */
size_t OLED::write(uint8_t c) 
{
#if 0
  if (!gfxFont)
    { return Adafruit_ST7735::write(c);}// 'Classic' built-in font
  if((textsize_x!=1 ) || (textsize_y!=1))  
    { return Adafruit_ST7735::write(c);}
#endif
    xAssert(gfxFont);
    xAssert(textsize_x==1 && textsize_y==1);
  
    if (c == '\n') 
    {
      cursor_x = 0;
      cursor_y +=          textsize_y * gfxFont->yAdvance;
      return 1;
    } 
    if(c=='\r')
      return 1;
    uint8_t first = gfxFont->first;
    if ((c < first) || (c > gfxFont->last)) 
        return 1;
    
    GFXglyph *glyph = gfxFont->glyph + c-first;
    int w = glyph->width,   h = glyph->height;
    if ((w <= 0) || (h <= 0)) 
    {
        cursor_x += glyph->xAdvance ;    
        return 1;
    }

    int xo = glyph->xOffset; // sic
    if (wrap && ((cursor_x +  (xo + w)) > _width)) 
    {
      cursor_x = 0;
      cursor_y +=   gfxFont->yAdvance;
    }
#if 0        
        drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x,  textsize_y);
#else
        // this one is about 10 times faster
        myDrawChar(cursor_x, cursor_y, c, textcolor, textbgcolor); 
#endif
      
    cursor_x += glyph->xAdvance ;    
    return 1;
}
#endif