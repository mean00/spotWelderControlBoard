/*
  OLED_I2C.h - Arduino/chipKit library support for 128x64 pixel SSD1306 OLEDs
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library has been made to make it easy to use 128x64 pixel OLED displays
  based on the SSD1306 controller chip with an Arduino or a chipKit.

  You can always find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#pragma once

#include "ssd1306_cmd.h"
#include "Arduino.h"
#include "gfxfont.h"


#define SSD1306_ADDR		0x3C

#define LEFT	0
#define RIGHT	9999
#define CENTER	9998

#define SSD1306_COMMAND			0x00
#define SSD1306_DATA			0xC0
#define SSD1306_DATA_CONTINUE           0x40

#define RST_NOT_IN_USE	255

struct _current_font
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
	uint8_t inverted;
};
#define fontbyte(x) cfont.font[x]  
#define bitmapbyte(x) bitmap[x]
#define bitmapdatatype unsigned char*

class OLED
{
public:
        typedef enum FontSize
        {
            SmallFont,MediumFont,BigFont
        };
        class FontInfo
        {
        public:
          int               maxHeight;          
          int               maxWidth;
          uint16_t         *filler;
          const GFXfont    *font;        
        };  
        FontInfo          fontInfo[3];
        
        FontInfo          *currentFont;
        const GFXfont           *gfxFont;
public: // extra functions
                void    drawRLEBitmap(int widthInPixel, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)    ;
                void    myDrawChar(int16_t x, int16_t y, unsigned char c,  uint16_t color, uint16_t bg) ;                
                void    setFontSize(FontSize size);
                void    setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big);
	public:
                        OLED( uint8_t rst_pin);
		void	begin();
		void	setBrightness(uint8_t value);
		void	clrScr();
		void	fillScr();
		void	invert(bool mode);
		void	setPixel(uint16_t x, uint16_t y);
		void	clrPixel(uint16_t x, uint16_t y);
		void	invPixel(uint16_t x, uint16_t y);
		void	invertText(bool mode);
		void	print(char *st, int x, int y);
		void	print(String st, int x, int y);
		void	printNumI(long num, int x, int y, int length=0, char filler=' ');
		void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ');
		void	setFont(uint8_t* font);
		void	drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy);
		void	drawLine(int x1, int y1, int x2, int y2);
		void	clrLine(int x1, int y1, int x2, int y2);
		void	drawRect(int x1, int y1, int x2, int y2);
		void	clrRect(int x1, int y1, int x2, int y2);
		void	drawRoundRect(int x1, int y1, int x2, int y2);
		void	clrRoundRect(int x1, int y1, int x2, int y2);
		void	drawCircle(int x, int y, int radius);
		void	clrCircle(int x, int y, int radius);
       //
       virtual  void    sendCommand(uint8_t cmd)=0;
       virtual  void    update()=0;
       //
	protected:
		uint8_t			_rst_pin;
		_current_font           cfont;
		uint8_t			scrbuf[1024];

		void	_print_char(unsigned char c, int x, int row);
		void	_convert_float(char *buf, double num, int width, byte prec);
		void	drawHLine(int x, int y, int l);
		void	clrHLine(int x, int y, int l);
		void	drawVLine(int x, int y, int l);
		void	clrVLine(int x, int y, int l);
};

