This is a modified version of the SSD1306 driver from http://www.RinkyDinkElectronics.com/
What are the changes ? 
* The access to the device is done through derivation. So just write your derived class providing the sendCommand and update functions for YOUR platform, for YOUR connectivity (i2c/spi). No #ifdef all around the place + you keep the code optimized for a specific platform.
* Truetype font support from Adafruit. Not perfect but good enough
* There is not a lot of sanity check in the code, it slows things down
* stm32duino/i2c provided as example, it is easy to add others (stm32duino/spi , esp32/...)
