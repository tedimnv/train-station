#include <iostream>
#include "AgeCard.h"

namespace constants
{
    const int FIRST_DISCOUNT = 100;
    const int SECOND_DISCOUNT = 50;
	const int THIRD_DISCOUNT = 20;
}


AgeCard::AgeCard(int age)
{
    void getAge(int age);
}

void AgeCard::setAge(int age)
{
	if (age < 1)
	{
		this->cardHolderAge = 0;
        std::cout << "Wrong input! Age should be a positive number. " << std::endl;
	}

	this->cardHolderAge = age;
}


void AgeCard::setDiscount()
{
    int percentage = 0;

    if (cardHolderAge >= 1 && cardHolderAge <= 10)
        percentage = constants::FIRST_DISCOUNT;
    else if (cardHolderAge >= 11 && cardHolderAge <= 18)
        percentage = constants::SECOND_DISCOUNT;
    else
        percentage = constants::THIRD_DISCOUNT;

    this->DiscountCard::setDiscountPercentage(percentage);
}