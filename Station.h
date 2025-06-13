#pragma once

#include <string>
#include <vector>
#include "Train.h"

class Station
{
    char* name;
	int пlatform;
	Train** trains;
	size_t trainsCount;

    //departingTrains и arrivingTrains 

public:
    void addTrain(Train*);
    //std::vector<Train*> getArrivingTrains(); //без vector
    //std::vector<Train*> getDepartingTrains(); //без vector
    int getFreePlatform(const Time& time);
};