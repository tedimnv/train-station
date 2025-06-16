#pragma once
#include "User.h"

class Admin : public User
{
    std::string username;
    std::string password;

public:

    Admin(std::string username, std::string password):username(username),password(password){}

    bool operator==(const Admin& other)
    {
        return other.username == username && other.password == password;
    }

    
    // void addWagonFirstClass(int trainID, int wagonType, double basePrice, double comfortFactor);
    // void addWagonSecondClass(int trainID, int wagonType, double basePrice, double pricePerKg);
    // void addWagonThirdClass(int trainID, int wagonType, double basePrice, double pricePer100Km);
    // void moveWagon(int sourceTrainID, int wagonID, int destinationTrainID);
    // void createAgeDiscountCard(std::string cardType, std::string userName, std::string fileName);  //
    // void createDistanceDiscountCard(std::string cardType, std::string userName, std::string fileName);  //
    // void createRouteDiscountCard(std::string cardType, std::string userName, std::string fileName);    //
    // void validateDiscountCard(int cardID);
};