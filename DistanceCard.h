#pragma once

#include "DiscountCard.h"

class DistanceCard : public DiscountCard
{
    double travelDistance;
    double maxDistance;

public:

    DistanceCard(double maxDistance, double travelDistance);
    
    void setDiscount();
    void getMaxDistance(double maxDistance);
    void getTravelDistance(double travelDistance);
};