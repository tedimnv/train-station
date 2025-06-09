#pragma once

#include "Time.h"
#include "Train.h"
#include "Wagon.h"

class Ticket
{
    Time timeOfPurchase;
    Train train;
    Wagon wagon;
    double discount;
};

void saveToFile(); //да се запази във файл