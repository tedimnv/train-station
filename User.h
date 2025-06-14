#pragma once
#include <string>
#include "Station.h"
#include "Train.h"
#include "Wagon.h"


class User
{
public:
    static void printStations();
    static void printSchedule(); // (Station* station)
    void printScheduleDestination(char* station, char* destination);
    void printScheduleTime(char* station, int day, int month, int year, int hour, int minute);
    void printTrain(int trainID);
    void printWagon(int trainID, int wagonID);
    void buyTicket(int trainID, int wagonID, int seatNum);
    void buyTicketWithDiscount(int trainID, int wagonID, int seatNum);
};

