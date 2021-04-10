/*--------------------------------------------------------------------
  The WS2812B library is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  It is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  See <http://www.gnu.org/licenses/>.
  --------------------------------------------------------------------*/

#pragma once
#include <Arduino.h>

class WS2812B
{
public:

  // Constructor: number of LEDs
        WS2812B (uint16_t number_of_leds); // Constuctor 
        ~WS2812B ();
  void  begin (void);
  void  show (void);
  void  setPixelColor (uint16_t n, uint8_t r, uint8_t g, uint8_t b);  
  void  setPixelColor (uint16_t n, uint32_t c);
  void  setBrightness (uint8_t);
  void  clear ();
  void  updateLength (uint16_t n);
  uint8_t  getBrightness (void) const;
  uint16_t numPixels (void) const;
  static uint32_t  Color (uint8_t r, uint8_t g, uint8_t b);
  static uint32_t  Color (uint8_t r, uint8_t g, uint8_t b, uint8_t w);
  inline bool  canShow (void)
  {
    return (micros () - endTime) >= 300L;
  }

protected:

  boolean   begun; // true if begin() previously called
  uint16_t  numLEDs; // Number of RGB LEDs in strip
  uint16_t  numBytes; // Size of 'pixels' buffer

  uint8_t   brightness;
  uint8_t   *pixels; // Holds the current LED color values, which the external API calls interact with 9 bytes per pixel + start + end empty bytes
  uint8_t   *doubleBuffer; // Holds the start of the double buffer (1 buffer for async DMA transfer and one for the API interaction.
  uint8_t   rOffset; // Index of red byte within each 3- or 4-byte pixel
  uint8_t   gOffset; // Index of green byte
  uint8_t   bOffset; // Index of blue byte
  uint8_t   wOffset; // Index of white byte (same as rOffset if no white)
  uint32_t  endTime; // Latch timing reference
};



