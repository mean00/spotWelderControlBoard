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
        virtual void redrawStockScreen(Welder::Selection sel, float voltage, Welder::TriggerType triggerType, int durationMs)=0;
        virtual      ~MyScreen() {}
protected:        
        MyScreen() {};
};

MyScreen *createScreen();