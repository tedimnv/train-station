#include <iostream>
#include "Wagon.h"

void Wagon::printSeats(int seatCount) const
{

}

bool Wagon::isSeatAvailable(int seatNumber)
{

}

void Wagon::bookSeat(int seatNumber)
{

}

const int Wagon::getStartingPrice() const
{
    return this->startingPrice;
}

void Wagon::setSeats(size_t seatsCount)
{
    if (seatsCount <= 0)
	{
		this->seats = nullptr;
		std::cout << "Wrong input! Seat count should be a positive number.";
	}
    this->seats = new bool[seatsCount]; // {false};
}