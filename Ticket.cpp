#include "Ticket.h"
#include <fstream>


void Ticket::saveToFile(const std::string& fileName) 
{
    std::ofstream file(fileName);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file << "=== TRAIN TICKET ===\n";
    file << "Purchase Time: ";
    printTimeToFile(file, timeOfPurchase); // Ще трябва да създадеш тази функция
    file << "\n";
    file << "Train ID: " << train.getId() << "\n";
    file << "Route: " << train.getStartingStation()->getStationName() 
         << " -> " << train.getFinalStation()->getStationName() << "\n";
    file << "Departure: ";
    printTimeToFile(file, train.getDepartureTime());
    file << " from platform " << train.getDeparturePlatform() << "\n";
    file << "Arrival: ";
    printTimeToFile(file, train.getArrivalTime());
    file << " to platform " << train.getArrivalPlatform() << "\n";
    file << "Wagon ID: " << wagon->getId() << "\n";
    file << "Seat: " << seatID << "\n";
    file << "Base Price: " << basePrice << " BGN\n";
    if (discountApplied > 0) {
        file << "Discount Applied: " << discountApplied << " BGN\n";
    }
    file << "Final Price: " << finalPrice << " BGN\n";
    file << "=====================\n";
    
    file.close();
}