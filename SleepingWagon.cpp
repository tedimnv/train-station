#include <iostream>
#include "SleepingWagon.h"

double SleepingWagon::calculatePrice(double startingPrice, double pricePer100Km, int distance)
{
    return startingPrice + (pricePer100Km/100) * distance;
}

double SleepingWagon::ticketPrice()
{
    
}