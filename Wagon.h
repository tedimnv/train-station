#pragma once

class Wagon //abstract
{
    int wagonID;
    double startingPrice;
    bool* seats;
    
   // Seat** seats;

    void setWagonID();
    void setStartingPrice(double startingPrice);
    void setSeats(size_t seatsCount);
    
    
public:
    
    virtual void printSeats(int seatCount) const = 0;
    bool isSeatAvailable(int seatNumber);
    void bookSeat(int seatNumber);

    const int getStartingPrice() const;
    virtual double ticketPrice() = 0;
    

    // const int chars = "===Age Card===" +1; >> <<
};

struct Seat
{
    int seatNumber;
    bool taken;
};
