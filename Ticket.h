#pragma once

#include "Time.h"
#include "Train.h"
#include "Wagon.h"

class Ticket
{
    Time timeOfPurchase;
    Train train;
    Wagon* wagon;
    int seatID;
    double basePrice;
    double discountApplied;
    double finalPrice;

public:
    void saveToFile(const std::string& fileName);
};

void saveToFile(); //да се запази във файл