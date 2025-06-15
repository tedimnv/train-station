#pragma once
#include "Time.h"
#include "TrainRepo.h"

class Train;

class Station: public TrainRepo
{
    std::string name;
	std::vector<int> platforms;
    std::vector<Train*> arrivingTrains;
	int trainsCount;
    
public:

    Station(std::string name) : name(name){};
    std::string getStationName() const
    {
        return name;
    }

    std::vector<Train*> getArrivingTrains();
    std::vector<Train*> getDepartingTrains();
    int getFreePlatform(const Time& time);

    void printDepartingTrains();
    void printArrivingTrains();
};