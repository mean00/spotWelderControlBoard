#pragma once

class MyScreen
{
public:
        virtual void clear()=0;
        virtual void update()=0;
        virtual void print(const char *t, int x, int y)=0;
        virtual void printBigNumber(const char *t, int x, int y)=0;
        virtual      ~MyScreen() {}
protected:        
        MyScreen() {};
};

MyScreen *createScreen();