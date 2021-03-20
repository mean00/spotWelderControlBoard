
#pragma once

class Navigate
{
public:
    enum Event
    {
        E_PUSH=1,
        E_TIMER
    };
                Navigate(Navigate *p)
                {
                    _parent=p;
                }
    virtual ~Navigate() {_parent=NULL;}
    virtual Navigate *handleEvent(Event evt,bool &subMenu)=0;
    virtual void  handleRotary(int inc)=0;
    virtual void redraw()=0;
protected:
    Navigate     *_parent;
};