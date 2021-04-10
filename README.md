
This is under development

Description
-----
This is a STM32F103 based replacement control board for the cheap red spot welder.
It completely replaces the original top board.
It is written in c++/Arduino using Roger Clark Stm32duino + cmake build system + FreeRTOS.
(Yes , it is overkill, but it's free, we have plenty of ram/flash so no need to be a cheap bastard here).

Small demo video
-----

[Small Youtube demo ](https://www.youtube.com/watch?v=iqqSZQ6BELQ)

Pics
-----

![screenshot](web/welder_casing.jpg?raw=true "front")
![screenshot](web/welder_pcb.jpg?raw=true "front")

 Shopping list (~ 10 $ )
 -----
* SSD1306 0.9" I2C LCD screen (easy to port if you want to use something else)
* BluePill board
* Rotary encoder
* Few caps/resistors/diode
* 2 cheap N Mosfets (SI2300 or similar, 5$ for 100 on ebay). It must have a gate threshold voltage well below 3v!.

The schematic is in the schematic folder.

Features
------
* Automatic or pedal driven solder pulse
* Pulse duration from 5 ms to 30 ms
* Settings (trigger & pulse duration & battery voltage offset) are stored in flash
* Try to be safe (emphasis on try)

How to build ?
-------
* Install arduino IDE
* Edit platformConfig.Cmake to put arduino path / toolchain to use
* mkdir build && cd build && cmake .. && make

Warning 
------
Be absolutely sure to upgrade the power board else it __WILL__ blow up at some point.
Look at the videos from Lucas on youtube, you __need__ to add the inrush current limiting resistor.
