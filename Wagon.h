#pragma once

class Wagon //abstract
{
    int wagonID;
    int startingPrice;
    std::vector<Seat> seats; //без vector 

public:
    
    virtual void printSeats(int seatCount) const = 0;
    bool isSeatAvailable(int seatNumber);
    void bookSeat(int seatNumber);

    virtual double ticketPrice() = 0;
};

struct Seat
{
    int seatNumber;
    bool taken;
};
