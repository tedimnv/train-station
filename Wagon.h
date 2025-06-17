#pragma once
#include <vector>

struct Seat 
{
    int seatNumber;
    bool taken;
};

class Wagon //abstract
{
    static int nextWagonID;  // генериране на ID
    int wagonID;
    double startingPrice;    
    std::vector<Seat> seats;

    
public:

    void setWagonID()
    { 
        wagonID = nextWagonID++; 
    }

    Wagon() { setWagonID(); }  
    virtual ~Wagon() = default;

    void setStartingPrice(double price)
    { 
        startingPrice = price; 
    }
    
    void setSeats(int seatsCount)
    {
        seats.clear();
        for (int i = 1; i <= seatsCount; i++) 
        {
            seats.push_back({i, false});
        }
    }

    int getId() const
    { 
        return wagonID; 
    }


    virtual void printSeats(int seatCount) const = 0;
    bool isSeatAvailable(int seatNumber) const
    {
        for (const auto& seat : seats) 
        {
            if (seat.seatNumber == seatNumber) 
            {
                return !seat.taken;
            }
        }
        return false;
    }

    void bookSeat(int seatNumber)
    {
        for (auto& seat : seats) 
        {
            if (seat.seatNumber == seatNumber) 
            {
                seat.taken = true;
                break;
            }
        }
    }

    bool hasBookedSeats() const
    {
        for (const auto& seat : seats) 
        {
            if (seat.taken) {
                return true;
            }
        }
        return false;
    }

    const int getStartingPrice() const
    { 
        return startingPrice; 
    }

    virtual double ticketPrice() = 0;

    void releaseSeat(int seatNumber)
    {
        for (auto& seat : seats)
        {
            if (seat.seatNumber == seatNumber)
            {
                seat.taken = false;
                break;
            }
        }
    }
    
    

    // const int chars = "===Age Card===" +1; >> <<
};


