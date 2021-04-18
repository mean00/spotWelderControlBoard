#pragma once


#define PIN_VBAT     PA1
#define PIN_DETECT   PA2
#define PIN_PEDAL    PA3
#define PIN_GATE     PB1


#define GATE_TIMER   3 //T3C1
#define GATE_CHANNEL 4

#define SCREEN_DATA  PB7
#define SCREEN_SCL   PB6
#define SCREEN_RESET PB5

#define BUZZER_GATE  PB0 //t3c3


#define ROTARY_LEFT  PA10
#define ROTARY_RIGHT PA9
#define ROTARY_PUSH  PA8

#define MIN_VBAT     11. // 11 v minimum !
#define MAX_PULSE    40 // in ms
#define MIN_PULSE    5  // in ms