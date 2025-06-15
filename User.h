#pragma once
#include <string>
#include "Station.h"
#include "Train.h"
#include "Wagon.h"


class User
{
public:
    static void printStations();
    static void printSchedule(std::string station);
    void printScheduleDestination(std::string station, std::string destination);
    void printScheduleTime(std::string station, std::string date, std::string time);
    void printTrain(int trainID);
    void printWagon(int trainID, int wagonID);
    void buyTicket(int trainID, int wagonID, int seatNum, std::string fileName);
    void buyTicketFirstClass(int trainID, int wagonID, int seatNum, std::string fileName, bool includesFood);
    void buyTicketSecondClass(int trainID, int wagonID, int seatNum, std::string fileName, int kgLuggage);
    void buyTicketWithDiscount(int trainID, int wagonID, int seatNum, std::string fileName, std::string discountFileName);
    void buyTicketFirstClassWithDiscount(int trainID, int wagonID, int seatNum, std::string fileName, std::string discountFileName, bool includesFood);
    void buyTicketSecondClassWithDiscount(int trainID, int wagonID, int seatNum, std::string fileName, std::string discountFileName, int kgLuggage);

};

