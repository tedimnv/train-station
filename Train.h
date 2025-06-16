#pragma once
#include "Time.h"
#include "Wagon.h"

class Station;

class Train
{
    int trainId;
    const Station* startingStation;
    const Station* finalStation;
    TimePoint departureTime;
    TimePoint arrivalTime;
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

    const Station* getStartingStation() 
    {
        return startingStation;
    }

    void setFinalStation(const Station* station)
    {
        finalStation = station;
    }

    const Station* getFinalStation() 
    {
        return finalStation;
    }

    int getId() const 
    {
        return trainId;
    }

    void setDepartureTime(TimePoint tp) 
    {
        departureTime = tp;
    }
    
    TimePoint getDepartureTime() const 
    {
        return departureTime;
    }

    void setArrivalTime(TimePoint tp) 
    {
        arrivalTime = tp;
    }

    TimePoint getArrivalTime() const 
    {
        return arrivalTime;
    }

    void setDeparturePlatform(int p) 
    { 
        departurePlatform = p; 
    }

    int getDeparturePlatform() const
    {
        return departurePlatform;
    }

    void setArrivalPlatform(int p) 
    { 
        arrivalPlatform = p; 
    }

    int getArrivalPlatform() const
    {
        return arrivalPlatform;
    }

   

    void setSpeed(int s) {
        speed = s;
    }
    
    void setDistance(double d) {
        distance = d;
    }
    
    void addWagon(Wagon* wagon) {
        wagons.push_back(wagon);
    }

     void removeWagon(int wagonID) {
        wagons.erase(
            std::remove_if(wagons.begin(), wagons.end(),
                [wagonID](Wagon* w) { return w->getId() == wagonID; }),
            wagons.end()
        );
    }
    
    Wagon* getWagonByID(int wagonID) {
        for (Wagon* wagon : wagons) {
            if (wagon->getId() == wagonID) {
                return wagon;
            }
        }
        return nullptr;
    }
    
    bool hasDeparted(const TimePoint& currentTime) {
        return currentTime >= departureTime;
    }
    
    bool hasArrived(const TimePoint& currentTime) {
        return currentTime >= arrivalTime;
    }

};

