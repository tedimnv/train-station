#include <iostream>
#include <cstring>
#include <fstream>
#include "RouteCard.h"

namespace constants
{
    const int ROUTE_DISCOUNT = 100; // 100% for matching routes
    const int NO_ROUTE_DISCOUNT = 0; // 0% for non matching routes
}

RouteCard::RouteCard(const std::string& name, const std::string& dest)
    : destination(dest)
{
    setCardHolder(name);
    setClassType("RouteCard");
    generateID();
    setDiscount();
}

void RouteCard::setDiscount()
{
    setDiscountPercentage(constants::ROUTE_DISCOUNT);
}

bool RouteCard::isApplicable(const std::string& route, double distance) const
{
    return (route.find(destination) != std::string::npos || route == applicableRoute);
}

void RouteCard::saveToFile(const std::string& fileName) const
{
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file << "=== DISCOUNT CARD ===" << std::endl;
    file << "Card Type: " << getClassType() << std::endl;
    file << "Card ID: " << getID() << std::endl;
    file << "Card Holder: " << getCardHolderName() << std::endl;
    file << "Applicable Destination: " << destination << std::endl;
    file << "Discount: " << getDiscountPercentage() << "%" << std::endl;
    file << "=====================" << std::endl;
    
    file.close();
}
