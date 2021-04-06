
This is under development

Description
-----
This is a STM32F103 based replacement control board for the cheap red spot welder.
It completely replaces the top board of the cheap red spot welder.
It is written in c++/Arduino using Roger Clark Stm32duino + cmake build system + FreeRTOS.
(Yes , it is overkill, but it's free, so no need to do it cheaply there)

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
* 2 cheap N Mosfet (SI2300 or similar, 5$ for 100 on ebay)

The schematic is in the schematic folder.

Features
------
* Automatic or pedal driven solder pulse
* Pulse duration from 5 ms to 30 ms
* Settings (trigger & pulse duration & battery voltage offset) are stored in flash
* Try to be safe (emphasis on try)
