#include <iostream>
#include "DistanceCard.h"

namespace constants
{
    const int FIRST_DISCOUNT = 50;
    const int SECOND_DISCOUNT = 30;
}


DistanceCard::DistanceCard(double maxDistance, double travelDistance)
{
    void getMaxDistance(double maxDistance);
    void getTravelDistance(double distance);
}


void DistanceCard::getMaxDistance(double maxDistance)
{

}

void DistanceCard::getTravelDistance(double travelDistance)
{

}

void DistanceCard::setDiscount()
{
    int percentage = 0;

    if (travelDistance <= maxDistance)
        percentage = constants::FIRST_DISCOUNT;
    else
        percentage = constants::SECOND_DISCOUNT;

    this->setDiscountPercentage(percentage);
}