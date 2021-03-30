#include "ssd1306_i2c.h"

/**
 * \fn checkFont
 * \brief extract max width/ max height from the font
 */
static void checkFont(const GFXfont *font, OLEDCore::FontInfo *info)
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

void  OLEDCore::print(int x, int y,const char *z)
{
    cursor_x=x;
    cursor_y=y;
   int l=strlen(z);
   while(*z)
   {
       int inc=write(*z);
       cursor_x+=inc;
       z++;
   }
}

/**
 * 
 * @param small
 * @param medium
 * @param big
 */
void  OLEDCore::setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big)
{
    checkFont(small, fontInfo+0);
    checkFont(medium,fontInfo+1);
    checkFont(big,   fontInfo+2);
}       


/**
 * 
 * @param x
 * @param y
 * @param c
 * @param color
 * @param bg
 */

void OLEDCore::square(int x,int y,int w, int h, bool color)
{
    
    if(color)
    {
        for(int xx=x;xx<x+w;xx++)
        for(int yy=y;yy<y+h;yy++)
            
            {
        	setPixel(xx,64-yy);
            }
    }else
    {
        for(int xx=x;xx<x+w;xx++)
        for(int yy=y;yy<y+h;yy++)
            
            {
        	clrPixel(xx,64-yy);
            }
        
    }
}

void OLEDCore::myDrawChar(int16_t x, int16_t y, unsigned char c,  bool invert) 
{
    int cr=c;
    cr -= gfxFont->first;
    GFXglyph *glyph =  gfxFont->glyph + cr;
    uint8_t *bitmap = gfxFont->bitmap;

    int bo = glyph->bitmapOffset;
    int w = glyph->width;
    int h = glyph->height;
    int yAdvance=currentFont->maxHeight;
    
    
   
    y+=glyph->yOffset;
    
    // fill left and right
    square(x,y,glyph->xOffset,h,invert);    
    x+=glyph->xOffset;
    square(x+w,y,glyph->xAdvance-w,h,invert);
    
    // fill top &and bottom
    
    int dex=0;

    int bits = 0, bit = 0;
    int n=h*w;
    int mask=0;
    uint8_t *data=bitmap+bo;
    for(int hh=0;hh<h;hh++)
    {
        int ty=64-(y+hh);   
        int bi=ty%8;
        int bimask=1<<bi;
        int notbimask=~bimask;
        int start=((ty/8)*128);
        if(ty<0 || ty>128)
        {
            dex+=w/8; // this is incomplete ! should not happen though
        }
        else
        for(int ww=0;ww<w;ww++)
        {
            if (!mask) 
            {
              bits = *data++;       
              mask=0x80;
            }
            bool set=!!   (bits & mask) ;
            set^=invert;
            
            int tx=(x+ww);
            if(tx>=0 && tx<128 )
            {
                int by=start+tx;
                if(set)
                    scrbuf[by]|=bimask;
                else
                    scrbuf[by]&=notbimask;                
            }
            mask>>=1;
            dex++;
        }
    }
}
/**
 * 
 * @param size
 */
void  OLEDCore::setFontSize(FontSize size)
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
 
/**
 * 
 * @param c
 * @return 
 */
int OLEDCore::write(uint8_t c) 
{

    if (c == '\n') 
    {
      cursor_x = 0;
      cursor_y +=           gfxFont->yAdvance;
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
    if ( ((cursor_x +  (xo + w)) > 128)) 
    {
      cursor_x = 0;
      cursor_y +=   gfxFont->yAdvance;
    }
    myDrawChar(cursor_x, cursor_y, c, inverted); 
    cursor_x += glyph->xAdvance ;    
    return 1;
}
/**
 * This could be optimized ** A LOT ** by swapping x & y in the source image
 * @param widthInPixel
 * @param height
 * @param wx
 * @param wy
 * @param fgcolor
 * @param bgcolor
 * @param data
 */
void OLEDCore::drawRLEBitmap(int widthInPixel, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{    

    bool first=true;
    int nbPixel=widthInPixel*height;
    int pixel=0;
    
    int mask=0;
    int cur;   
    
    int ready=0;
    int repeat;
    bool color;
    for( int yy=0;yy<height;yy++)      
        for(int xx=0;xx<widthInPixel;)
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
                        color=true;
                    }else
                        color=false;
                    mask>>=1;                
                    if(color) 
                        setPixel(wx+xx,64-(wy+yy));
                    else 
                        clrPixel(wx+xx,64-(wy+yy));
                    xx++;
                }
                    
            }
            
        }
}
 
