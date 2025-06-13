#include <iostream>
#include "DiscountCard.h"

namespace constants
{
	const int ID_CHARECTERS_COUNT = 6;
}

void DiscountCard::setDiscountPercentage(int percentage)
{
    this->discountPercentage = percentage;
}

void DiscountCard::getID(int id)
{
	std::srand(std::time(0));

    id = 0;
    for (int i = 0; i < constants::ID_CHARECTERS_COUNT; i++) 
    {
        int digit = std::rand() % 10;
        id = id * 10 + digit;
    }

    
    if (id < 100000) 
        id += 100000;
    
    this->ID = id;
}

void DiscountCard::isApplicable()
{
    if(ID != 10) // не e от документа to be fixed
        discountPercentage = 0;

    //четем от текстов документ с различни IDs и проверяваме дали е там
}