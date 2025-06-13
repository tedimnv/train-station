#include <iostream>
#include <cstring> // for strlen, strcpy
#include "RouteCard.h"

namespace constants
{
    const int DISCOUNT = 100;
}

// Constructor
RouteCard::RouteCard(const char* dest, const char* r) 
{
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);

    route = new char[strlen(r) + 1];
    strcpy(route, r);
}

void RouteCard::getDestination(char *destination)
{

}

void RouteCard::getRoute(char *route)
{

}

void RouteCard::setDiscount()
{
    int percentage = 0;

    if(destination == route)
        percentage = constants::DISCOUNT;

    this->setDiscountPercentage(percentage);
}

// Destructor
RouteCard::~RouteCard() 
{
    delete[] destination;
    delete[] route;
}