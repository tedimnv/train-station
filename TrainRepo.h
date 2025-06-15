#pragma once
#include <vector>
#include "Train.h"

class TrainRepo
{
public:

    void addTrain(const Train& train)
    {
        trains.push_back(train);
    }

    void removeTrain(int id)
    {
        for (auto it = trains.begin(); it != trains.end(); i++)
        {
            if (it->getId() == id) 
            {
                trains.erase(it);
                return;                
            }
        }
    }

    const Train * getById(int id) const
    {
        for (size_t i = 0; i < trains.size(); i++) 
        {
            if (trains[i].getId() == id) 
            {
                return &(trains[i]);
            }
        }
        return nullptr;
    }

private:
    std::vector<Train> trains;
};