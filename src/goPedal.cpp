#include "goPedal.h"
extern bool detectConnection();

Navigate *spawnGoPedal(Navigate *parent, Pedal &p)
{
    Navigate *gp= new GoPedal(parent,p);
    return gp;
}
bool GoPedal::start()
{
    _pedal.arm();
    return true;
}

bool GoPedal::triggered()
{
    bool detected=_pedal.pushed();
    return detected;
}
bool GoPedal::contact()
{
    return detectConnection();
}

// EOF