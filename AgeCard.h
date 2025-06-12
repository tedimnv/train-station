#pragma once

#include "DiscountCard.h"

class AgeCard : public DiscountCard
{
    int age;

public:
    double discountSum(double startingPrice, int discountPercentage) const override;
};
