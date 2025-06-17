#pragma once
#include "Time.h"
#include "TrainRepo.h"

class Train;

class Station: public TrainRepo
{
    std::string name;
	std::vector<int> platforms;
    std::vector<Train*> arrivingTrains;
    std::vector<Train*> departingTrains;
	int trainsCount;
    int nextPlatformId;
    
public:

    Station(std::string name) : name(name){};
    std::string getStationName() const
    {
        return name;
    }

    std::vector<Train*>& getArrivingTrains() 
    {
        return arrivingTrains;
    }

      std::vector<Train*>& getDepartingTrains() 
    {
        return departingTrains;
    }

    int getFreePlatform(const TimePoint& time)
    {
        for (int platform : platforms)
        {
            if (isPlatformFree(platform, time))
            {
                return platform;
            }
        }
        
        // ако няма свободен коловоз
        int newPlatform = nextPlatformId++;
        platforms.push_back(newPlatform);
        return newPlatform;
    }

    void addDepartingTrain(Train* train)
    {
        departingTrains.push_back(train);
        trainsCount++;
    }
    
    void addArrivingTrain(Train* train)
    {
        arrivingTrains.push_back(train);
    }


    void printDepartingTrains() const
    {
        std::cout << "Departing trains from " << name << ":" << std::endl;
        for (const Train* train : departingTrains)
        {
            std::cout << "Train ID: " << train->getId() << ", Platform: " << train->getDeparturePlatform() << std::endl;
        }
    }
    
    void printArrivingTrains() const
    {
        std::cout << "Arriving trains to " << name << ":" << std::endl;
        for (const Train* train : arrivingTrains)
        {
            std::cout << "Train ID: " << train->getId() << ", Platform: " << train->getArrivalPlatform() << std::endl;
        }
    }

private:

    bool isPlatformFree(int platformId, const TimePoint& time)
    {
        // заминаващите влакове
        for (const Train* train : departingTrains)
        {
            if (train->getDeparturePlatform() == platformId)
            {
                //  буфер от 30 минути - горе-долу достатъчни за престой на влака
                auto bufferTime = std::chrono::minutes(30);
                if (time >= train->getDepartureTime() - bufferTime && 
                    time <= train->getDepartureTime() + bufferTime)
                {
                    return false;
                }
            }
        }

        // пристигащите влакове
        for (const Train* train : arrivingTrains)
        {
            if (train->getArrivalPlatform() == platformId)
            {
                auto bufferTime = std::chrono::minutes(30);
                if (time >= train->getArrivalTime() - bufferTime && 
                    time <= train->getArrivalTime() + bufferTime)
                {
                    return false;
                }
            }
        }
        
        return true;
    }
  
};