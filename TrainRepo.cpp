#include <iostream>
#include "TrainRepo.h"

void TrainRepo::addTrain(const Train &train)
{
    trains.push_back(train);
}

void TrainRepo::removeTrain(int id)
{
    for (auto it = trains.begin(); it != trains.end(); it++)
        {
            if (it->getId() == id) 
            {
                trains.erase(it);
                return;                
            }
        }
}

const Train *TrainRepo::getById(int id) const
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