#pragma once
#include "User.h"

class Admin : public User
{
    std::string username;
    std::string password;

public:
    bool login(std::string username, std::string password);
    void addStation(std::string station);
    void addTrain(std::string station, std::string destination, int distance, int speed, std::string date, std::string time);
    void removeTrain(int trainID);
    void addWagon(int trainID);
    void moveWagon();
    void createDiscountCard();
    void validateDiscountCard();
};