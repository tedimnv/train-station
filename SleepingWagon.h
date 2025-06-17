#pragma once

#include "Wagon.h"

class SleepingWagon : public Wagon
{
    double pricePer100Km;
    int distance;

public:

    void printSeats(int seatCount) const override
    {
        std::cout << "Sleeping Wagon Beds:\n";
        for (int i = 1; i <= seatCount; i++) 
        {
            std::cout << "Bed " << i << ": " << (isSeatAvailable(i) ? "Available" : "Taken") << "\n";
        }
    }

    static inline double calculatePrice(double startingPrice, double pricePer100Km, int distance);

    double ticketPrice() override;

    void setPricePer100Km(double price) 
    { 
        pricePer100Km = price; 
    }

    double getPricePer100Km() const 
    { 
        return pricePer100Km; 
    }


    void setDistance(int dist) 
    { 
        distance = dist; 
    }

    int getDistance() 
    { 
        return distance; 
    }

};