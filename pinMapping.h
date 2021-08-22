#pragma once

// Timer mapping
// ADC is using                Timer 3 channel 3
// MOSFET pin is using  PB1 => Timer 2 channel 3
// Buzzer is using      PB0 => Timer 2 channel 2
// LED:                 PB3 => Timer 1 channel 1
//                      


#define PIN_VBAT     PA1
#define PIN_DETECT   PA2
#define PIN_PEDAL    PA3
#define PIN_GATE     PB1
#define PIN_LED      PB3

#define GATE_TIMER   2 
#define GATE_CHANNEL 3

#define SCREEN_DATA  PB7
#define SCREEN_SCL   PB6
#define SCREEN_RESET PB5

#define BUZZER_GATE  PB0 


#define ROTARY_LEFT  PB8
#define ROTARY_RIGHT PB9

#define ROTARY_PUSH  PB11


#define MIN_VBAT     11. // 11 v minimum !
#define MAX_PULSE    50 // in ms
#define MIN_PULSE    5  // in ms
