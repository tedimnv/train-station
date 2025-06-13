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


void AgeCard::getAge(int age)
{
    if(age <= 0)
        std::cout << "Wrong input! Age should be a positive number. " << std::endl;
}


void AgeCard::setDiscount()
{
    int percentage = 0;

    if (age >= 1 && age <= 10)
        percentage = constants::FIRST_DISCOUNT;
    else if (age >= 11 && age <= 18)
        percentage = constants::SECOND_DISCOUNT;
    else
        percentage = constants::THIRD_DISCOUNT;

    this->setDiscountPercentage(percentage);
}