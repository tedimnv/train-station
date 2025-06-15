#pragma once
#include <vector>
#include "Station.h"

class StationsRepo
{
public:

    void addStation(std::string station)
    {
        stations.push_back(Station(station));
    }

    const std::vector<Station>& getAll() const
    {
        return stations;
    }

    Station * findByName(const std::string& name) 
    {
        for (size_t i = 0; i < stations.size(); i++) 
        {
            if (stations[i].name == name) 
            {
                return &stations[i];
            }
        }
        return nullptr;
    }

private:
    std::vector<Station> stations;
};