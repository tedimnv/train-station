#include <iostream>
#include "SleepingWagon.h"

double SleepingWagon::calculatePrice(double startingPrice, double pricePer100Kmint, int distance)
{
    return startingPrice + (pricePer100Km/100) * distance;
}

double SleepingWagon::ticketPrice()
{
    
}