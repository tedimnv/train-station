#include <iostream>
#include "SleepingWagon.h"

double SleepingWagon::calculatePrice(double startingPrice, double pricePer100Km, int distance) 
{
    return startingPrice + (pricePer100Km * distance / 100.0);
}

double SleepingWagon::ticketPrice() 
{
    return calculatePrice(getStartingPrice(), pricePer100Km, distance);
}