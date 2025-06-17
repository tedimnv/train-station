#pragma once

#include "DiscountCard.h"

class AgeCard : public DiscountCard
{
private:
    int cardHolderAge;

public:
    AgeCard(const std::string& name, int age);
    
    void setAge(int age);
    void setDiscount() override;
    bool isApplicable(const std::string& route = "", double distance = 0) const override;
    void saveToFile(const std::string& fileName) const override;
    
    int getCardHoldersAge() const { return cardHolderAge; }
};
