#pragma once
#include "Wagon.h"

class WagonFinder 
{
private:
    int targetID;
public:
    WagonFinder(int id) : targetID(id) {}
    bool operator()(Wagon* w) const 
    {
        return w->getId() == targetID;
    }
};