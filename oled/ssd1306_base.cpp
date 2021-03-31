/*
  OLED_I2C.cpp - Arduino/chipKit library support for 128x64 pixel SSD1306 OLEDs
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

#include "ssd1306_base.h"
#include "Wire.h"

OLEDCore::OLEDCore( uint8_t rst_pin)
{ 
	_rst_pin = rst_pin;
        cursor_x=0;
        cursor_y=0;
        inverted=false;
}


void OLEDCore::begin()
{
	if (_rst_pin != RST_NOT_IN_USE)
	{
		pinMode(_rst_pin, OUTPUT);
		digitalWrite(_rst_pin, HIGH);
		delay(1);
		digitalWrite(_rst_pin, LOW);
		delay(10);
		digitalWrite(_rst_pin, HIGH);
	}
	
        
    sendCommand(SSD1306_DISPLAY_OFF);
    sendCommand(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    sendCommand(0x80);
    sendCommand(SSD1306_SET_MULTIPLEX_RATIO);
    sendCommand(0x3F);
    sendCommand(SSD1306_SET_DISPLAY_OFFSET);
    sendCommand(0x0);
    sendCommand(SSD1306_SET_START_LINE | 0x0);
    sendCommand(SSD1306_CHARGE_PUMP);
    sendCommand(0x14);
    sendCommand(SSD1306_MEMORY_ADDR_MODE);
    sendCommand(0x00);
    sendCommand(SSD1306_SET_SEGMENT_REMAP | 0x1);
    sendCommand(SSD1306_COM_SCAN_DIR_DEC);
    sendCommand(SSD1306_SET_COM_PINS);
    sendCommand(0x12);
    sendCommand(SSD1306_SET_CONTRAST_CONTROL);
    sendCommand(0xCF);
    sendCommand(SSD1306_SET_PRECHARGE_PERIOD);
    sendCommand(0xF1);
    sendCommand(SSD1306_SET_VCOM_DESELECT);
    sendCommand(0x40);
    sendCommand(SSD1306_DISPLAY_ALL_ON_RESUME);
    sendCommand(SSD1306_NORMAL_DISPLAY);
    sendCommand(SSD1306_DISPLAY_ON);

    clrScr();
    update();

}

void OLEDCore::clrScr()
{
	memset(scrbuf, 0, 1024);
}

void OLEDCore::fillScr()
{
	memset(scrbuf, 255, 1024);
}

void OLEDCore::setBrightness(uint8_t value)
{
    sendCommand(SSD1306_SET_CONTRAST_CONTROL);
    sendCommand(value);
}

void OLEDCore::invert(bool mode)
{
    if (mode==true)
        sendCommand(SSD1306_INVERT_DISPLAY);
    else
        sendCommand(SSD1306_NORMAL_DISPLAY);
}

void OLEDCore::setPixel(uint16_t x, uint16_t y)
{
    int by, bi;

    if ((x>=0) and (x<128) and (y>=0) and (y<64))
    {
        by=((y/8)*128)+x;
        bi=y % 8;

        scrbuf[by]=scrbuf[by] | (1<<bi);
    }
}

void OLEDCore::clrPixel(uint16_t x, uint16_t y)
{
    int by, bi;

    if ((x>=0) and (x<128) and (y>=0) and (y<64))
    {
        by=((y/8)*128)+x;
        bi=y % 8;

        scrbuf[by]=scrbuf[by] & ~(1<<bi);
    }
}

void OLEDCore::invPixel(uint16_t x, uint16_t y)
{
    int by, bi;

    if ((x>=0) and (x<128) and (y>=0) and (y<64))
    {
        by=((y/8)*128)+x;
        bi=y % 8;

        if ((scrbuf[by] & (1<<bi))==0)
            scrbuf[by]=scrbuf[by] | (1<<bi);
        else
            scrbuf[by]=scrbuf[by] & ~(1<<bi);
    }
}

void OLEDCore::drawHLine(int x, int y, int l)
{
    int by, bi;

    if ((x>=0) and (x<128) and (y>=0) and (y<64))
    {
        for (int cx=0; cx<l; cx++)
        {
            by=((y/8)*128)+x;
            bi=y % 8;

            scrbuf[by+cx] |= (1<<bi);
        }
    }
}

void OLEDCore::clrHLine(int x, int y, int l)
{
    int by, bi;

    if ((x>=0) and (x<128) and (y>=0) and (y<64))
    {
        for (int cx=0; cx<l; cx++)
        {
            by=((y/8)*128)+x;
            bi=y % 8;

            scrbuf[by+cx] &= ~(1<<bi);
        }
    }
}

void OLEDCore::drawVLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) and (x<128) and (y>=0) and (y<64))
	{
		for (int cy=0; cy<l; cy++)
		{
			setPixel(x, y+cy);
		}
	}
}

void OLEDCore::clrVLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) and (x<128) and (y>=0) and (y<64))
	{
		for (int cy=0; cy<l; cy++)
		{
			clrPixel(x, y+cy);
		}
	}
}

void OLEDCore::drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=(double(y2-y1)/double(x2-x1));
		ty=double(y1);
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				setPixel(i, int(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				setPixel(i, int(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=(float(x2-x1)/float(y2-y1));
		tx=float(x1);
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		setPixel(int(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		setPixel(int(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void OLEDCore::clrLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		clrHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		clrVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=(double(y2-y1)/double(x2-x1));
		ty=double(y1);
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				clrPixel(i, int(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				clrPixel(i, int(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=(float(x2-x1)/float(y2-y1));
		tx=float(x1);
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		clrPixel(int(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		clrPixel(int(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void OLEDCore::drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1+1);
}

void OLEDCore::clrRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	clrHLine(x1, y1, x2-x1);
	clrHLine(x1, y2, x2-x1);
	clrVLine(x1, y1, y2-y1);
	clrVLine(x2, y1, y2-y1+1);
}

void OLEDCore::drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		setPixel(x1+1,y1+1);
		setPixel(x2-1,y1+1);
		setPixel(x1+1,y2-1);
		setPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-3);
		drawHLine(x1+2, y2, x2-x1-3);
		drawVLine(x1, y1+2, y2-y1-3);
		drawVLine(x2, y1+2, y2-y1-3);
	}
}

void OLEDCore::clrRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		clrPixel(x1+1,y1+1);
		clrPixel(x2-1,y1+1);
		clrPixel(x1+1,y2-1);
		clrPixel(x2-1,y2-1);
		clrHLine(x1+2, y1, x2-x1-3);
		clrHLine(x1+2, y2, x2-x1-3);
		clrVLine(x1, y1+2, y2-y1-3);
		clrVLine(x2, y1+2, y2-y1-3);
	}
}

void OLEDCore::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	setPixel(x, y + radius);
	setPixel(x, y - radius);
	setPixel(x + radius, y);
	setPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setPixel(x + x1, y + y1);
		setPixel(x - x1, y + y1);
		setPixel(x + x1, y - y1);
		setPixel(x - x1, y - y1);
		setPixel(x + y1, y + x1);
		setPixel(x - y1, y + x1);
		setPixel(x + y1, y - x1);
		setPixel(x - y1, y - x1);
	}
}

void OLEDCore::clrCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	clrPixel(x, y + radius);
	clrPixel(x, y - radius);
	clrPixel(x + radius, y);
	clrPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		clrPixel(x + x1, y + y1);
		clrPixel(x - x1, y + y1);
		clrPixel(x + x1, y - y1);
		clrPixel(x - x1, y - y1);
		clrPixel(x + y1, y + x1);
		clrPixel(x - y1, y + x1);
		clrPixel(x + y1, y - x1);
		clrPixel(x - y1, y - x1);
	}
}

void OLEDCore::drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy)
{
	int bit;
	byte data;

	for (int cy=0; cy<sy; cy++)
	{
		bit= cy % 8;
		for(int cx=0; cx<sx; cx++)
		{
			data=bitmapbyte(cx+((cy/8)*sx));
			if ((data & (1<<bit))>0)
				setPixel(x+cx, y+cy);
			else
				clrPixel(x+cx, y+cy);
		}
	}      
}
