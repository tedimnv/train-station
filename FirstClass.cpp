#include <iostream>
#include "FirstClass.h"

double FirstClass::calculatePrice(double startingPrice, double comfortFactor, bool includesFood)
{
    int foodPrice;

    if (includesFood) 
        foodPrice = 10;
    else 
        foodPrice = 0;

    return startingPrice * comfortFactor + foodPrice;
}

double FirstClass::ticketPrice()
{
    return this->getStartingPrice()*this->comfortFactor + this->includesFood*constants::FOOD_PRICE;
}
