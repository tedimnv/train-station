#include <iostream>
#include "User.h"

void User::printStations()
{
    std::cout << "Print Stations test. \n";
}

void User::printSchedule()
{
    
    std::cout << " === Schedule for station Sofia === \n";
    std::cout << " \n";
    std::cout << " Arrivals: \n";
    std::cout << " ----------------------------------------------------------------------------- \n";
    std::cout << "| Arrival time: | Arrival platform: | Train ID: | Starting station: | Status: |\n";
    std::cout << " ----------------------------------------------------------------------------- \n";
    std::cout << " ------------------------------------------ \n";

}

void User::printScheduleDestination(char *station, char *destination)
{

}

void User::printScheduleTime(char *station, int day, int month, int year, int hour, int minute)
{

}

void User::printTrain(int ID)
{

}

void User::printWagon(int trainID, int wagonID)
{

}

void User::buyTicket(int trainID, int wagonID, int seatNum)
{

}

void User::buyTicketWithDiscount(int trainID, int wagonID, int seatNum)
{

}