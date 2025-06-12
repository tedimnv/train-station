#pragma once

#include "Wagon.h"

class SleepingWagon : public Wagon
{
    double pricePer100Km;
    int distance;

public:
    virtual double calculatePrice(double startingPrice, double pricePer100Km, int distance);
    double ticketPrice() override;
};