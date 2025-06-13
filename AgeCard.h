#pragma once

#include "DiscountCard.h"

class AgeCard : public DiscountCard
{
    int age;

public:

    AgeCard(int age);

    void setDiscount();
    void getAge(int age);
};
