#include "sunflowersuns.h"

sunFlowerSuns::sunFlowerSuns()
{
}

void sunFlowerSuns::advance(int phase)
{
    if(!phase) return;  // We don't do anything to prepare objects for advancing
    move(0);
}

void sunFlowerSuns::move(double time)
{
    yCoordinate = yCoordinate + ( yVelocity * time);
}
