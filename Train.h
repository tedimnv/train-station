#pragma once

#include "Time.h"
#include "Station.h"

class Train
{
    int trainID;
    Station* StartingStation;
    Station* FinalStation;
    Time DepartureTime;
    Time ArrivalTime;
    int departurePlatform;
    int arrivalPlatform;
    double distance;
    int speed;
    // wagons - без vector
};

