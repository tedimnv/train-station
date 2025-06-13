#pragma once

#include "DiscountCard.h"

class RouteCard : public DiscountCard
{
    char* destination;
    char* route;

public:
    RouteCard(const char* destination, const char* route); // Constructor
    ~RouteCard(); // Destructor

    void getDestination(char* destination);
    void getRoute(char* route);
    void setDiscount();
   
    // RouteCard(char destination[], char route[]);
    // RouteCard(int id_, const char* dest);             // Constructor
    // RouteCard(const RouteCard& other);                // Copy constructor
    // RouteCard& operator=(const RouteCard& other);     // Copy assignment
    // ~RouteCard();                                     // Destructor

    // void getDestination(char* destination);
    // void getRoute(char* route);
};

