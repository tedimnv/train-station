#pragma once
#include "Time.h"
#include "Train.h"
#include "Wagon.h"
#include "Station.h"

class Ticket
{
    TimePoint timeOfPurchase;
    Train train;
    Wagon* wagon;
    int seatID;
    double basePrice;
    double discountApplied;
    double finalPrice;
    
public:
    void setTimeOfPurchase(const TimePoint& time) 
    { 
        timeOfPurchase = time; 
    }

    void setTrain(const Train& t) 
    { 
        train = t; 
    }

    void setWagon(Wagon* w) 
    { 
        wagon = w; 
    }

    void setSeatID(int id) 
    { 
        seatID = id; 
    }

    void setBasePrice(double price) 
    { 
        basePrice = price; 
    }

    void setDiscountApplied(double discount) 
    { 
        discountApplied = discount; 
    }

    void setFinalPrice(double price) 
    { 
        finalPrice = price; 
    }
    
    void saveToFile(const std::string& fileName);
};

