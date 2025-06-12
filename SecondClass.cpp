#include <iostream>
#include "SecondClass.h"

double SecondClass::calculatePrice(double startingPrice, int luggageKg, double pricePerKg)
{
    return startingPrice + pricePerKg * luggageKg;
}

double SecondClass::ticketPrice()
{
    
}