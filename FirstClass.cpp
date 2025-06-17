#include <iostream>
#include "FirstClass.h"


double FirstClass::ticketPrice() 
{
    int foodPrice = includesFood ? constants::FOOD_PRICE : 0;
    return getStartingPrice() * comfortFactor + foodPrice;
}