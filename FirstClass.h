#pragma once

#include "Wagon.h"

namespace constants
{
    const int SEATS_COUNT = 10;
    const int FOOD_PRICE = 10;
}
class FirstClass : public Wagon
{
    double comfortFactor; //from 0-1 
    bool includesFood;

public:
    virtual double calculatePrice(double Price, double comfortFactor, bool includesFood);
    double ticketPrice() override; 

};

