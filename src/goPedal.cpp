#include "goPedal.h"
extern bool detectConnection();

Navigate *spawnGoPedal(Navigate *parent, Pedal &p)
{
    return new GoPedal(parent,p);
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