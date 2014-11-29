#ifndef SUNFLOWERSUNS_H
#define SUNFLOWERSUNS_H

#include "sunpoints.h"

class sunFlowerSuns : public sunpoints
{
public:
    sunFlowerSuns();
    void advance(int phase);
    void move(double time);
};

#endif // SUNFLOWERSUNS_H
