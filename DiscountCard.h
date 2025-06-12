#pragma once

class DiscountCard
{
    // име без string!!
    int code; //6 цифри randomizer

public:
    virtual double discountSum(double startingPrice, int discountPercentage) const = 0;
    virtual bool isApplicable() const = 0;
};
