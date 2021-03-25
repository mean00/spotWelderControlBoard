/*
 
 STM32duino info here : http://wiki.stm32duino.com/index.php?title=Generic_pin_mapping
 */
// Rotary encoder part : Derived from  Rotary encoder handler for arduino * Copyright 2011 Ben Buxton. Licenced under the GNU GPL Version 3. * Contact: bb@cactii.net
// Debounce part derived from http://www.kennethkuhn.com/electronics/debounce.c


#include <Wire.h>
#include "MapleFreeRTOS1000_pp.h"
#include "rotary.h"
#include "dso_debug.h"

#define ROTARY_FULL_STEP
#define THRESHOLD 200 // in ms


#include "rotary_internal.h"
#define ButtonToPin(x)    (PB0+x)
#define pinAsInput(x)     pinMode(ButtonToPin(x),INPUT_PULLUP);
#define attachRE(x)       attachInterrupt(ButtonToPin(x),_myInterruptRE,(void *)x,FALLING );


  
static TaskHandle_t taskHandle;
int ints=0;

/**
 * \brief This one is for left/right
 * @param a
 */
static void _myInterruptRE(void *a)
{
    Rotary *r=(Rotary *)a;
    r->interruptRE();
}
static void _myInterruptPush(void *a)
{
    Rotary *r=(Rotary *)a;
    r->interruptPush();
}

/**
 * 
 */
Rotary::Rotary(int left, int right, int push)
{
    _pinL=left;
    _pinR=right;
    _pinPush=push;
    
    _state = R_START;
    _pushed=0;
    _lastPush=0;
      
    
#define SETUP_PIN(x)    pinMode(x,OUTPUT); digitalWrite(x,1);pinMode(x,INPUT_PULLUP);
    
    SETUP_PIN(_pinL);
    SETUP_PIN(_pinR);
    SETUP_PIN(_pinPush);   
}

/**
 * 
 * @return 
 */
bool Rotary::setup()
{
    attachInterrupt(_pinL,_myInterruptRE,this,CHANGE );
    attachInterrupt(_pinR,_myInterruptRE,this,CHANGE );
    attachInterrupt(_pinPush,_myInterruptPush,this,FALLING );
    return true;
}
/**
 * 
 * @param a
 */

void Rotary::interruptRE()
{   
  int reg=GPIOA->regs->IDR;
  int l= !!(reg&(1<<_pinL));
  int r= !!(reg&(1<<_pinR));
  int pinstate =  l+l+r;
  // Determine new state from the pins and state table.
  _state = ttable[_state & 0xf][pinstate];
  // Return emit bits, ie the generated event.
  switch(_state&DIR_MASK)
  {
    case DIR_CW:
            _counter--;
            break;
    case DIR_CCW: 
            _counter++;
            break;
    default: 
            break;
  }
}
/**
 * 
 */
#define ROUNDUP 0xffff
void Rotary::interruptPush()
{
    int now=millis()&ROUNDUP;
    if(now<_lastPush) now+=ROUNDUP+1;
    if((now-_lastPush)<THRESHOLD) 
    {
        return;
    }
    _lastPush=now;
    this->_pushed++;
}

/**
 * 
 * @return 
 */
int  Rotary::getRotaryValue()
{
    // Avoid disabling interrupts    
    int evt = __atomic_exchange_n( &(_counter), 0, __ATOMIC_SEQ_CST);
    return evt;
}
/**
 * 
 * @return 
 */
int    Rotary::getPush()
{
    int evt = __atomic_exchange_n( &(this->_pushed), 0, __ATOMIC_SEQ_CST);
    if(evt)
    {
        Logger("Pushed!\n");
    }
    return evt;
}

//
