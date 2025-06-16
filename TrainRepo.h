#pragma once
#include <vector>
#include "Train.h"

class TrainRepo
{
public:

    void addTrain(const Train& train);
    void removeTrain(int id);
    const Train * getById(int id) const;
    
private:
    std::vector<Train> trains;
};