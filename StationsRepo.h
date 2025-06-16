#pragma once
#include <vector>
#include "Station.h"

class StationsRepo
{
public:

    void addStation(std::string station);
    const std::vector<Station>& getAll() const;
    Station * findByName(const std::string& name);

    bool removeTrainById(int trainId) 
    {
        bool trainFound = false;
        
        // минаваме през всички гари
        for (Station& station : stations) 
        {
            auto& departingTrains = station.getDepartingTrains();
            for (auto it = departingTrains.begin(); it != departingTrains.end(); ++it) 
            {
                if ((*it)->getId() == trainId) 
                {
                    delete *it;
                    departingTrains.erase(it);
                    trainFound = true;
                    break;
                }
            }
            
            auto& arrivingTrains = station.getArrivingTrains();
            for (auto it = arrivingTrains.begin(); it != arrivingTrains.end(); ++it) 
            {
                if ((*it)->getId() == trainId) 
                {
                    arrivingTrains.erase(it);
                    break;
                }
            }
        }
        
        return trainFound;
    }

    Train* findTrainById(int trainId) 
    {
        for (Station& station : stations) 
        {
            const auto& departingTrains = station.getDepartingTrains();
            for (Train* train : departingTrains) 
            {
                if (train->getId() == trainId) 
                {
                    return train;
                }
            }
        }
        return nullptr;
    }

private:
    std::vector<Station> stations;
};