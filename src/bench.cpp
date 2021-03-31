
#include <Wire.h>
#include "MapleFreeRTOS1000_pp.h"
#include "printf.h"
#include "dso_debug.h"
#include "screen.h"
#include "assets.h"
extern MyScreen *myScreen;

// RLE : Base = 18 ms

void bench2()
{
    
   while(1)
    {
        char st[10];
        int before=millis();
        myScreen->clear();
        myScreen->rleDisplay(splash_width, splash_height, 2 , 6, splash);
        myScreen->update();
        int after=millis();
        Logger("Bench RLE = %d\n",after-before);
   }
}

// emppty 28 ms
// 4 big print =>30 ms  @ 400 khz
// 4 big print =>18 ms  @ 800 Khz
// 4 big print =>15 ms  @ 1000 Khz // invert 17
//  4 big print =>FAIL  @ 2000 Khz

void bench1()
{
    int counter=0;
    myScreen->invertText(true);
    while(1)
    {
        char st[10];
        int before=millis();
        myScreen->clear();
        sprintf(st,"a%03d",counter);
        myScreen->printBig(st,1,56);
        myScreen->update();
        int after=millis();
        Logger("Bench = %d\n",after-before);
        counter++;
    }
}

void bench()
{
    bench2();
}