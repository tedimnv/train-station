#include <iostream>
#include "StationsRepo.h"

void StationsRepo::addStation(std::string station)
{
    stations.push_back(Station(station));
}

const std::vector<Station> &StationsRepo::getAll() const
{
    return stations;
}

Station *StationsRepo::findByName(const std::__1::string &name)
{
    for (size_t i = 0; i < stations.size(); i++) 
        {
            if (stations[i].getStationName() == name)
            {
                return &stations[i];
            }
        }
        return nullptr;
}