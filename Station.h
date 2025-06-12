#pragma once

#include <string>
#include <vector>
#include "Train.h"

class Station
{
    std::string name; // без string 
    int platform; //не трябва да е с int рабери как без vector
    //departingTrains и arrivingTrains 

public:
    void addTrain(Train*);
    std::vector<Train*> getArrivingTrains(); //без vector
    std::vector<Train*> getDepartingTrains(); //без vector
    int getFreePlatform(const Time& time);
};