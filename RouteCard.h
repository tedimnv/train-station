#pragma once

#include "DiscountCard.h"

class RouteCard : public DiscountCard
{
    private:
    std::string destination;
    std::string applicableRoute;

public:
    RouteCard(const std::string& name, const std::string& destination);
    
    void setDiscount() override;
    bool isApplicable(const std::string& destination = "", double distance = 0) const override;
    void saveToFile(const std::string& fileName) const override;
    
    std::string getDestination() const 
    { 
        return destination; 
    }
};