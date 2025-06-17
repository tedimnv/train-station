#include <iostream>
#include <fstream>
#include "DistanceCard.h"

namespace constants
{
    const int SHORT_DISTANCE_DISCOUNT = 50;  // distance <= maxDistance 50% 
    const int LONG_DISTANCE_DISCOUNT = 30;   // distance > maxDistance 30% 
}

DistanceCard::DistanceCard(const std::string& name, double maxDistance) : maxDistance(maxDistance)
{
    setCardHolder(name);
    setClassType("DistanceCard");
    generateID();
    setDiscount();
}

void DistanceCard::setDiscount()
{
    setDiscountPercentage(constants::SHORT_DISTANCE_DISCOUNT);
}

bool DistanceCard::isApplicable(const std::string& route, double distance) const
{
    if (distance <= maxDistance) 
    {
        return true; // will get SHORT_DISTANCE_DISCOUNT
    } else 
    {
        return true; // will get LONG_DISTANCE_DISCOUNT  
    }
}

void DistanceCard::saveToFile(const std::string& fileName) const
{
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file << "=== DISCOUNT CARD ===" << std::endl;
    file << "Card Type: " << getClassType() << std::endl;
    file << "Card ID: " << getID() << std::endl;
    file << "Card Holder: " << getCardHolderName() << std::endl;
    file << "Max Distance: " << maxDistance << " km" << std::endl;
    file << "Short Distance Discount (≤" << maxDistance << "km): " << constants::SHORT_DISTANCE_DISCOUNT << "%" << std::endl;
    file << "Long Distance Discount (>" << maxDistance << "km): " << constants::LONG_DISTANCE_DISCOUNT << "%" << std::endl;
    file << "=====================" << std::endl;
    
    file.close();
}