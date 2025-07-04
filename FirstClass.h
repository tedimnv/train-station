#pragma once

#include "Wagon.h"

namespace constants
{
    const int SEATS_COUNT = 10;
    const int FOOD_PRICE = 10;
}

class FirstClass : public Wagon
{
    double comfortFactor; //from 0-1 
    bool includesFood;

public:
    
    FirstClass(){};
    virtual ~FirstClass(){};
    virtual double ticketPrice() override;

    void printSeats(int seatCount) const override 
    {
        std::cout << "First Class Seats:\n";
        for (int i = 1; i <= seatCount; i++) 
        {
            std::cout << "Seat " << i << ": " << (isSeatAvailable(i) ? "Available" : "Taken") << "\n";
        }
    }

    static inline double calculatePrice(double Price, double comfortFactor, bool includesFood);

    void setComfortFactor(double factor)
    {
        comfortFactor = factor;
    }

    double getComfortFactor() const
    {
        return comfortFactor;
    }

    void setIncludesFood(bool food) 
    { 
        includesFood = food; 
    }

    bool getIncludesFood() const 
    { 
        return includesFood; 
    }

};

