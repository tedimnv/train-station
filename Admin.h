#pragma once
#include "User.h"

class Admin : public User
{
    std::string username;
    std::string password;

public:
    bool login(std::string username, std::string password);
    void addStation();
    void addTrain();
    void addWagon();
    void createDiscountCard();
    void validateDiscountCard();
};