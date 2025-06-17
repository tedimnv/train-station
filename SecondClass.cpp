#include <iostream>
#include "SecondClass.h"


double SecondClass::ticketPrice() 
{
    return calculatePrice(getStartingPrice(), luggageKg, pricePerKg);
}