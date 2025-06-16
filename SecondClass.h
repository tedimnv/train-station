#pragma once

#include "Wagon.h"

class SecondClass : public Wagon
{
    double pricePerKg;
    int luggageKg;

public:

    void printSeats(int seatCount) const override
    {
        std::cout << "Second Class Seats:\n";
        for (int i = 1; i <= seatCount; i++) 
        {
            std::cout << "Seat " << i << ": " << (isSeatAvailable(i) ? "Available" : "Taken") << "\n";
        }
    }

    static inline double calculatePrice(double startingPrice, int luggageKg, double pricePerKg);
    double ticketPrice() override;

    void setLuggageKg(int kg) 
    { 
        luggageKg = kg; 
    }

    void setPricePerKg(double price) 
    { 
        pricePerKg = price; 
    }
};