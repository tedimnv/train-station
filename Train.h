#pragma once
#include "Time.h"
#include "Wagon.h"

class Station;

class Train
{
    int trainId;
    Station* startingStation;
    Station* finalStation;
    Time DepartureTime;
    Time ArrivalTime;
    int departurePlatform;
    int arrivalPlatform;
    double distance;
    int speed;
    std::vector<Wagon*> wagons;

public:
    void setStartingStation(const Station* station)
    {
        startingStation = station;
    }

    void setFinalStation(const Station* station)
    {
        finalStation = station;
    }

    int getId() const {
        return trainId;
    }

    
    void addWagon(Wagon*);
    void removeWagon(int wagonID);
    Wagon* getWagonByID(int wagonID);
    void calculateArrivalTime(); //Конструктор, 
    //който изчислява arrivalDateTime на база 
    //departureDateTime, distanceKm и speedKmH.
    bool hasDeparted(const Time& currentTime);
    bool hasArrived(const Time& currentTime);
};

