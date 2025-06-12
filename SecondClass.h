#pragma once

#include "Wagon.h"

class SecondClass : public Wagon
{
    double pricePerKg;
    int luggageKg;

public:
    virtual double calculatePrice(double startingPrice, int luggageKg, double pricePerKg);
    double ticketPrice() override;
};