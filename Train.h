#pragma once
#include "Time.h"
#include "Wagon.h"

class Station;

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
    std::vector<Wagon*> wagons;

public:
    void addWagon(Wagon*);
    void removeWagon(int wagonID);
    Wagon* getWagonByID(int wagonID);
    void calculateArrivalTime(); //Конструктор, 
    //който изчислява arrivalDateTime на база 
    //departureDateTime, distanceKm и speedKmH.
    bool hasDeparted(const Time& currentTime);
    bool hasArrived(const Time& currentTime);
};

