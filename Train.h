#pragma once
#include "Time.h"
#include "Wagon.h"

class Station;

class Train
{
    static int nextTrainID;
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
    
    Train() 
    {
        trainId = nextTrainID++;
    }

    void setStartingStation(const Station* station)
    {
        startingStation = station;
    }

    const Station* getStartingStation() const
    {
        return startingStation;
    }

    void setFinalStation(const Station* station)
    {
        finalStation = station;
    }

    const Station* getFinalStation() const
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

    bool hasDeparted(const TimePoint& currentTime) const
    {
        return currentTime >= departureTime;
    }
    
    bool hasArrived(const TimePoint& currentTime) 
    {
        return currentTime >= arrivalTime;
    }

    void setSpeed(int s) 
    {
        speed = s;
    }
    
    void setDistance(double d) 
    {
        distance = d;
    }

    double getDistance() const
    {
        return distance;
    }
    
    void addWagon(Wagon* wagon) 
    {
        wagons.push_back(wagon);
    }

    void removeWagon(int wagonID) 
    {
        for (size_t i = 0; i < wagons.size(); ++i) {
            if (wagons[i]->getId() == wagonID) {
                delete wagons[i];  // Delete the wagon object first
                wagons.erase(wagons.begin() + i);
                break;  // Important: break after erasing to avoid issues
            }
        }
    }

    
    Wagon* getWagonByID(int wagonID) 
    {
        for (Wagon* wagon : wagons) 
        {
            if (wagon->getId() == wagonID) 
            {
                return wagon;
            }
        }
        return nullptr;
    }

    const std::vector<Wagon*>& getWagons() const
    {
        return wagons;
    }

    void removeWagonKeepObject(int wagonID) 
    {
        for (size_t i = 0; i < wagons.size(); ++i) {
            if (wagons[i]->getId() == wagonID) {
                wagons.erase(wagons.begin() + i);
                break;  // Important: break after erasing to avoid issues
            }
        }
    }

    ~Train() 
    {
        for (Wagon* wagon : wagons) 
        {
            delete wagon;
        }
        wagons.clear();
    }
};

