#pragma once

class MyScreen
{
public:
        enum Selection
        {
            None,
            Duration,
            Trigger,
            Settings,
            
            Max=Settings
        };
        enum TriggerType
        {
            Auto,
            Pedal
        };    
    
public:
        virtual void clear()=0;
        virtual void update()=0;
        virtual void print(const char *t, int x, int y)=0;
        virtual void printBigNumber(const char *t, int x, int y)=0;
        virtual void redrawStockScreen(Selection sel, float voltage, TriggerType triggerType, int durationMs)=0;
        virtual      ~MyScreen() {}
protected:        
        MyScreen() {};
};

MyScreen *createScreen();