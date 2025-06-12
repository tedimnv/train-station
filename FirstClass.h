#pragma once

#include "Wagon.h"

class FirstClass : public Wagon
{
    int seatCount = 10;
    double comfortFactor; //from 0-1 
    bool includesFood;

public:
    virtual double calculatePrice(double Price, double comfortFactor, bool includesFood);
    double ticketPrice() override; 

    // HELP W THIS ^^^
};

