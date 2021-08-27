


Description
-----
This is a GD32F1/F3/VF103 (or STM32F103) based replacement control board for the cheap red spot welder.
It completely replaces the original top board.
It is written  using the lnArduino framework, so it will work with GD32F1/F3/VF103 or STM32F103 mcu.

Small demo video
-----

[Small Youtube demo ](https://www.youtube.com/watch?v=iqqSZQ6BELQ)

Pics
-----

![screenshot](web/welder_casing.jpg?raw=true "top")
![screenshot](web/welder_pcb.jpg?raw=true "pcb")
![screenshot](web/redBoard.jpg?raw=true "red")
![screenshot](web/new_board.jpg?raw=true "raw_mcu")

 Shopping list (~ 10 $ )
 -----
* SSD1306 0.9" I2C LCD screen (easy to port if you want to use something else)
* BluePill board or just the MCU, it is setup to not use an external Xtal anyway.
* Rotary encoder
* Few caps/resistors/diode
* 3 cheap N Mosfets (SI2300 or similar, 5$ for 100 on ebay). It must have a gate threshold voltage well below 3v! (the NPN transistor on the schematic can be replaced by such a mosfet).

The schematic is in the schematic folder.

Features
------
* Automatic or pedal driven solder pulse
* Pulse duration from 5 ms to 50 ms
* Settings (trigger & pulse duration & battery voltage offset) are stored in flash
* Try to be safe (emphasis on try)

How to build ?
------- 
* Edit platformConfig.Cmake to put arduino path / toolchain to use
* Edit mcuSelect.cmake to fine tune your MCU
* mkdir build && cd build && cmake .. && make

Warning 
------
Be absolutely sure to upgrade the power board else it __WILL__ blow up at some point.
Look at the videos from Lucas on youtube, you __need__ to add the inrush current limiting resistor.
