#include <string>
#pragma once

class User
{
public:
    void printStations();
    void printSchedule(const std::string& stationName); //no string 
    void printTrain(int trainID);
    void printWagon(int trainID, int wagonID);
    void buyTicket(...);
    void buyTicketWithDiscount(...);
};

