#pragma once
#include "Time.h"

class Train;

class Station
{
    std::string name;
	std::vector<int> platforms;
    std::vector<Train*> departingTrains;
	int trainsCount;
    
public:

    void addTrain(Train*);
    std::vector<Train*> getArrivingTrains();
    std::vector<Train*> getDepartingTrains();
    int getFreePlatform(const Time& time);

    void printDepartingTrains();
    void printArrivingTrains();
};