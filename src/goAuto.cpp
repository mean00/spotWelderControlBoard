#include "goAuto.h"

Navigate *spawnGoAuto(Navigate *parent)
{
    return new GoAuto(parent);
}