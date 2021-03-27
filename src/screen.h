#pragma once
#include "welderUi.h"
class MyScreen
{
public:
    
    
public:
        virtual void clear()=0;
        virtual void update()=0;
        virtual void print(const char *t, int x, int y)=0;
        virtual void printBig(const char *t, int x, int y)=0;
        virtual void redrawStockScreen(Welder::Selection sel,  Welder::TriggerSource triggerType, int durationMs)=0;
        virtual void redrawArmScreen( int count, Welder::TriggerSource triggerType, int durationMs)=0;
        virtual void rleDisplay(int width, int height,int at_x, int at_y, const uint8_t *data)=0;
        virtual void disconnectMessage();
        virtual      ~MyScreen() {}
protected:        
        MyScreen() {};
};

MyScreen *createScreen();