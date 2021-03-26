#include "goAuto.h"
extern bool detectConnection();

Navigate *spawnGoAuto(Navigate *parent)
{
    return new GoAuto(parent);
}

bool GoAuto::triggered()
{
    bool detected=detectConnection();
    if(detected)
    {
        _detectionCounter++;
        if(_detectionCounter>10)
            return true;
        return false;
    }
    // reset
    _detectionCounter=0;
    return false;
}
bool GoAuto::contact()
{
    return detectConnection();
}

// EOF