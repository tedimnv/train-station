#pragma once

#include "DiscountCard.h"

class DistanceCard : public DiscountCard
{
private:
    double maxDistance;

public:
    
    DistanceCard(const std::string& name, double maxDistance);
    
    void setDiscount() override;
    bool isApplicable(const std::string& route = "", double distance = 0) const override;
    void saveToFile(const std::string& fileName) const override;
    
    double getMaxDistance() const { return maxDistance; }

};