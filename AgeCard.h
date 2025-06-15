#pragma once

#include "DiscountCard.h"

class AgeCard : public DiscountCard
{
    int cardHolderAge;

    void setDiscount();
    void setAge(int age);
    
public:
	 AgeCard(int age);
     AgeCard(const char* name, int age);

	const int getCardHoldersAge() const;
};
