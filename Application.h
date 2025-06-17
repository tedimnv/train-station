#pragma once
#include <sstream>
#include "AdminRepo.h"
#include "StationsRepo.h"
#include "TrainRepo.h"
#include "Time.h"
#include "FirstClass.h"
#include "SecondClass.h"
#include "SleepingWagon.h"
#include "Wagon.h"
#include "Ticket.h"
#include "AgeCard.h"
#include "DistanceCard.h"
#include "RouteCard.h"

// за print-schedule
bool compareTrainsByArrivalTime(const Train* a, const Train* b) 
{
    return a->getArrivalTime() < b->getArrivalTime();
}

bool compareTrainsByDepartureTime(const Train* a, const Train* b) 
{
    return a->getDepartureTime() < b->getDepartureTime();
}

class Application
{

public:
    
    
    void run()
    {
        std::string line;

        while(true)
        {
            std::getline(std::cin, line);
            std::stringstream ss(line);

            std::string command;

            ss >> command;

            if(command == "login")
            {

                if(isAdmin)
                {
                    std::cout << "Already logged in!\n";
                    continue;
                }

                std::string username;
                std::string password;

                ss >> username >> password;

                if(adminRepo.exists(username, password))
                {
                    isAdmin = true;
                    std::cout << "Welcome back, " << username << "!\n"; 
                }
                else
                {
                    std::cout << "Error: Incorrect credentials!\n";
                }
            }
            else if(command == "add-station")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }

                std::string name;

                ss >> name;

                stationRepo.addStation(name);

                std::cout << "Added station " << name << std::endl;
            }
            else if(command == "print-stations")
            {
                const std::vector <Station>& stations = stationRepo.getAll();
                for ( size_t i = 0 ; i < stations.size() ; i++) 
                {
                    std::cout << stations[i].getStationName() << std::endl;
                }
            }
            else if(command == "print-schedule")
            {
                std::string stationName;
                ss >> stationName;
                
                if (stationName.empty()) 
                {
                    std::cout << "Error: Please give a station name!\n";
                    continue;
                }
                
                Station* station = stationRepo.findByName(stationName);
                
                if (!station) 
                {
                    std::cout << "Error: No such station " << stationName << std::endl;
                    continue;
                }
                
                TimePoint currentTime = getCurrentTime();
                
                std::cout << "=== Schedule for station " << stationName << " ===" << std::endl;
                
                std::cout << "Arrivals:" << std::endl;
                std::cout << "|   Arrival Time   | Arrival Platform | Train ID | Starting station |" << std::endl;
                std::cout << " ------------------------------------------------------------------- " << std::endl;
                
                const std::vector<Train*>& arrivingTrains = station->getArrivingTrains();
                
                std::vector<Train*> sortedArrivingTrains = arrivingTrains;
                std::sort(sortedArrivingTrains.begin(), sortedArrivingTrains.end(), compareTrainsByArrivalTime);
                 
                for (const Train* train : sortedArrivingTrains) 
                {
                    std::cout << "| ";
                    printTime(train->getArrivalTime());
                    std::cout << " | " << train->getArrivalPlatform()  << "                | " << train->getId() << "           | " << train->getStartingStation()->getStationName() << "     |" << std::endl;
                }
                
                std::cout << std::endl;
                
                // Print Departures
                std::cout << "Departures:" << std::endl;
                std::cout << "|  Departure Time  |   Arrival Time   | Departure Platform | Train ID | Status | Destination |" << std::endl;
                std::cout << " --------------------------------------------------------------------------------------------" << std::endl;
                
                const std::vector<Train*>& departingTrains = station->getDepartingTrains();
                
                std::vector<Train*> sortedDepartingTrains = departingTrains;
                std::sort(sortedDepartingTrains.begin(), sortedDepartingTrains.end(), compareTrainsByDepartureTime);
    
                
                for (const Train* train : sortedDepartingTrains) 
                {
                    std::cout << "| ";
                    printTime(train->getDepartureTime());
                    std::cout << " | ";
                    printTime(train->getArrivalTime());
                    std::cout << " | "  << train->getDeparturePlatform() << "                  | " << train->getId() << "        | ";
                    
                    if (train->hasDeparted(currentTime)) 
                    {
                        std::cout << "Departed";
                    } 
                    else 
                    {
                        std::cout << "To depart";
                    }
                    
                    std::cout << " | "  << train->getFinalStation()->getStationName() << "   |";
                }
             
                std::cout << std::endl << std::endl;

            }
            else if(command == "print-schedule-destination")
            {
                std::string stationName;
                std::string destinationName;
                ss >> stationName >> destinationName;
                
                if (stationName.empty()) 
                {
                    std::cout << "Error: Please give a station name!\n";
                    continue;
                }
                
                if (destinationName.empty()) 
                {
                    std::cout << "Error: Please give a destination name!\n";
                    continue;
                }
                
                Station* station = stationRepo.findByName(stationName);
                
                if (!station) 
                {
                    std::cout << "Error: No such station " << stationName << std::endl;
                    continue;
                }
                
                Station* destination = stationRepo.findByName(destinationName);
                
                if (!destination) 
                {
                    std::cout << "Error: No such destination " << destinationName << std::endl;
                    continue;
                }
                
                TimePoint currentTime = getCurrentTime();
                
                std::cout << "=== Schedule for departures to  " << destinationName << " ===" << std::endl;
                
                const std::vector<Train*>& departingTrains = station->getDepartingTrains();
                std::vector<Train*> trainsToDestination;
                
                for (Train* train : departingTrains) 
                {
                    if (train->getFinalStation()->getStationName() == destinationName) 
                    {
                        trainsToDestination.push_back(train);
                    }
                }
                
                if (trainsToDestination.empty()) 
                {
                    std::cout << "No trains found from " << stationName << " to " << destinationName << std::endl;
                    continue;
                }
                
                std::sort(trainsToDestination.begin(), trainsToDestination.end(), compareTrainsByDepartureTime);
                
                std::cout << "Departures to " << destinationName << ":" << std::endl;
                std::cout << "|  Departure Time  |   Arrival Time   | Departure Platform | Train ID | Status |" << std::endl;
                std::cout << " ------------------------------------------------------------------------------ " << std::endl;
                
                for (const Train* train : trainsToDestination) 
                {
                    std::cout << "| ";
                    printTime(train->getDepartureTime());
                    std::cout << " | ";
                    printTime(train->getArrivalTime());
                    std::cout << " | " << train->getDeparturePlatform() << "                  | " << train->getId() << "        | ";
                    
                    if (train->hasDeparted(currentTime)) 
                    {
                        std::cout << "Departed";
                    } 
                    else 
                    {
                        std::cout << "To depart";
                    }
                    
                    std::cout << " |" << std::endl;
                }
                
                std::cout << std::endl;
            }
            else if(command == "print-schedule-time")
            {
                std::string stationName;
                ss >> stationName;
                
                if (stationName.empty()) 
                {
                    std::cout << "Error: Please give a station name!\n";
                    continue;
                }
                
                Station* station = stationRepo.findByName(stationName);
                
                if (!station) 
                {
                    std::cout << "Error: No such station " << stationName << std::endl;
                    continue;
                }
                
                // Parse the time from the remaining input
                TimePoint specifiedTime;
                try 
                {
                    specifiedTime = parseTime(ss);
                }
                catch (const std::exception& e) 
                {
                    std::cout << "Error: Invalid time format! Please use: DD MM YYYY HH MM\n";
                    continue;
                }
                
                std::cout << "=== Schedule for station " << stationName << " after ";
                printTime(specifiedTime);
                std::cout << " ===" << std::endl;
                
                // Filter departing trains that depart after the specified time
                const std::vector<Train*>& departingTrains = station->getDepartingTrains();
                std::vector<Train*> trainsAfterTime;
                
                for (Train* train : departingTrains) 
                {
                    if (train->getDepartureTime() > specifiedTime) 
                    {
                        trainsAfterTime.push_back(train);
                    }
                }
                
                if (trainsAfterTime.empty()) 
                {
                    std::cout << "No trains found departing from " << stationName << " after ";
                    printTime(specifiedTime);
                    std::cout << std::endl;
                    continue;
                }
                
                // Sort trains by departure time
                std::sort(trainsAfterTime.begin(), trainsAfterTime.end(), compareTrainsByDepartureTime);
                
                std::cout << "Departures after ";
                printTime(specifiedTime);
                std::cout << ":" << std::endl;
                std::cout << "|  Departure Time  |   Arrival Time   | Departure Platform | Train ID | Status | Destination |" << std::endl;
                std::cout << " --------------------------------------------------------------------------------------------" << std::endl;
                
                TimePoint currentTime = getCurrentTime();
                
                for (const Train* train : trainsAfterTime) 
                {
                    std::cout << "| ";
                    printTime(train->getDepartureTime());
                    std::cout << " | ";
                    printTime(train->getArrivalTime());
                    std::cout << " | " << train->getDeparturePlatform() << "                  | " << train->getId() << "        | ";
                    
                    if (train->hasDeparted(currentTime)) 
                    {
                        std::cout << "Departed";
                    } 
                    else 
                    {
                        std::cout << "To depart";
                    }
                    
                    std::cout << " | " << train->getFinalStation()->getStationName() << "   |" << std::endl;
                }
                
                std::cout << std::endl;
            }
            else if(command == "print-train")
            {
                int trainId;
                ss >> trainId;
                
                if (!ss) 
                {
                    std::cout << "Error: Please give a train ID!\n";
                    continue;
                }
                
                Train* train = stationRepo.findTrainById(trainId);
                
                if (!train) 
                {
                    std::cout << "Error: Train with ID " << trainId << " not found!\n";
                    continue;
                }
                
                std::cout << "=== Train Information ===" << std::endl;
                std::cout << "Train ID: " << train->getId() << std::endl;
                std::cout << "Route: " << train->getStartingStation()->getStationName() 
                        << " -> " << train->getFinalStation()->getStationName() << std::endl;
                std::cout << "Distance: " << train->getDistance() << " km" << std::endl;
                
                std::cout << "Departure: ";
                printTime(train->getDepartureTime());
                std::cout << " from platform " << train->getDeparturePlatform() << std::endl;
                
                std::cout << "Arrival: ";
                printTime(train->getArrivalTime());
                std::cout << " to platform " << train->getArrivalPlatform() << std::endl;
                
                TimePoint currentTime = getCurrentTime();
                std::cout << "Status: ";
                if (train->hasDeparted(currentTime)) 
                {
                    if (train->hasArrived(currentTime)) 
                    {
                        std::cout << "Arrived";
                    } 
                    else 
                    {
                        std::cout << "In transit";
                    }
                } 
                else 
                {
                    std::cout << "Scheduled to depart";
                }
                std::cout << std::endl;
                
                std::cout << "\n=== Wagons ===" << std::endl;
                
                const std::vector<Wagon*>& wagons = train->getWagons();
                
                if (wagons.empty()) 
                {
                    std::cout << "No wagons attached to this train." << std::endl;
                    std::cout << std::endl;
                    continue;
                }
                
                std::cout << "| Wagon ID | Type  | Starting Price | Ticket Price | Available Seats |" << std::endl;
                std::cout << " -------------------------------------------------------------------- " << std::endl;
                
                for (Wagon* wagon : wagons) 
                {
                    std::cout << "| "  << wagon->getId() << "        | ";
                        
                        // Determine wagon type by trying to cast to different types
                        FirstClass* firstClass = dynamic_cast<FirstClass*>(wagon);
                        SecondClass* secondClass = dynamic_cast<SecondClass*>(wagon);
                        SleepingWagon* sleepingWagon = dynamic_cast<SleepingWagon*>(wagon);
                        
                        if (firstClass) 
                        {
                            std::cout << "1st" << "   | ";
                            std::cout << wagon->getStartingPrice() << "             | ";
                            std::cout << wagon->ticketPrice() << "           | ";
                            
                            // Count available seats
                            int availableSeats = 0;
                            for (int seatNum = 1; seatNum <= constants::SEATS_COUNT; seatNum++) 
                            {
                                if (wagon->isSeatAvailable(seatNum)) 
                                {
                                    availableSeats++;
                                }
                            }
                            std::cout << availableSeats << "              |" << std::endl;
                            
                            std::cout << "         Details: Comfort Factor: " << firstClass->getComfortFactor() 
                                    << ", Food: " << (firstClass->getIncludesFood() ? "Yes" : "No") << std::endl;
                        }
                        else if (secondClass) 
                        {
                            std::cout << "2nd" << "   | ";
                            std::cout << wagon->getStartingPrice() << "             | ";
                            std::cout << wagon->ticketPrice() << "           | ";
                            
                            // Count available seats
                            int availableSeats = 0;
                            for (int seatNum = 1; seatNum <= constants::SEATS_COUNT; seatNum++) 
                            {
                                if (wagon->isSeatAvailable(seatNum)) 
                                {
                                    availableSeats++;
                                }
                            }
                            std::cout << availableSeats << "              |" << std::endl;
                        }
                        else if (sleepingWagon) 
                        {
                            std::cout << "Sleep" << " | ";
                            std::cout << wagon->getStartingPrice() << "             | ";
                            std::cout << wagon->ticketPrice() << "           | ";
                            
                            // Count available seats
                            int availableSeats = 0;
                            for (int seatNum = 1; seatNum <= constants::SEATS_COUNT; seatNum++) 
                            {
                                if (wagon->isSeatAvailable(seatNum)) 
                                {
                                    availableSeats++;
                                }
                            }
                            std::cout << availableSeats << "              |" << std::endl;
                            
                            std::cout << "         Details: Price per 100km: " << sleepingWagon->getPricePer100Km() << std::endl;
                        }
                        else 
                        {
                            std::cout << "Unknown" << " | ";
                            std::cout << wagon->getStartingPrice() << " | ";
                            std::cout << wagon->ticketPrice() << " | ";
                            
                            // Count available seats
                            int availableSeats = 0;
                            for (int seatNum = 1; seatNum <= constants::SEATS_COUNT; seatNum++) 
                            {
                                if (wagon->isSeatAvailable(seatNum)) 
                                {
                                    availableSeats++;
                                }
                            }
                            std::cout << availableSeats << " |" << std::endl;
                    }
                }
                
                std::cout << std::endl;
            }
            else if(command == "buy-ticket")
            {
                int trainId;
                int wagonId;
                int seatId;
                std::string ticketFileName;
                
                ss >> trainId >> wagonId >> seatId >> ticketFileName;
                
                if (!ss || ticketFileName.empty()) 
                {
                    std::cout << "Error: Please provide train ID, wagon ID, seat ID, and ticket file name!\n";
                    continue;
                }
                
                Train* train = stationRepo.findTrainById(trainId);
                if (!train) 
                {
                    std::cout << "Error: Train with ID " << trainId << " not found!\n";
                    continue;
                }
                
                TimePoint currentTime = getCurrentTime();
                if (train->hasDeparted(currentTime)) 
                {
                    std::cout << "Error: Cannot buy ticket for a train that has already departed!\n";
                    continue;
                }
                
                Wagon* wagon = train->getWagonByID(wagonId);
                if (!wagon) 
                {
                    std::cout << "Error: Wagon with ID " << wagonId << " not found in train " << trainId << "!\n";
                    continue;
                }
                
                if (!wagon->isSeatAvailable(seatId)) 
                {
                    std::cout << "Error: Seat " << seatId << " is not available in wagon " << wagonId << "!\n";
                    continue;
                }
                
                // тип на вагона и допълнителните параметри
                FirstClass* firstClass = dynamic_cast<FirstClass*>(wagon);
                SecondClass* secondClass = dynamic_cast<SecondClass*>(wagon);
                SleepingWagon* sleepingWagon = dynamic_cast<SleepingWagon*>(wagon);
                
                double finalPrice = wagon->getStartingPrice();
                double discountApplied = 0.0;
                
                if (firstClass) 
                {
                    finalPrice = firstClass->ticketPrice();
                    std::cout << "Purchasing first-class ticket...\n";
                }
                else if (secondClass) 
                {
                    int luggageWeight;
                    ss >> luggageWeight;
                    
                    if (!ss) 
                    {
                        std::cout << "Error: Please provide luggage weight for second-class ticket!\n";
                        continue;
                    }
                    
                    if (luggageWeight < 0) 
                    {
                        std::cout << "Error: Luggage weight cannot be negative!\n";
                        continue;
                    }
                    
                    secondClass->setLuggageKg(luggageWeight);
                    finalPrice = secondClass->ticketPrice();
                    std::cout << "Purchasing second-class ticket with " << luggageWeight << "kg luggage...\n";
                }
                else if (sleepingWagon) 
                {
                    finalPrice = sleepingWagon->ticketPrice();
                    std::cout << "Purchasing sleeping wagon ticket...\n";
                }
                else 
                {
                    std::cout << "Error: Unknown wagon type!\n";
                    continue;
                }
                
                wagon->bookSeat(seatId);
                
                Ticket ticket; //създаваме билета
                ticket.setTimeOfPurchase(currentTime);
                ticket.setTrain(*train);
                ticket.setWagon(wagon);
                ticket.setSeatID(seatId);
                ticket.setBasePrice(wagon->getStartingPrice());
                ticket.setDiscountApplied(discountApplied);
                ticket.setFinalPrice(finalPrice);
                
                try 
                {
                    ticket.saveToFile(ticketFileName);
                    
                    std::cout << "Ticket purchased successfully!\n\n";
                    std::cout << "=== Ticket Details ===\n";
                    std::cout << "Train ID: " << trainId << "\n";
                    std::cout << "Route: " << train->getStartingStation()->getStationName() 
                            << " -> " << train->getFinalStation()->getStationName() << "\n";
                    std::cout << "Departure: ";
                    printTime(train->getDepartureTime());
                    std::cout << " from platform " << train->getDeparturePlatform() << "\n";
                    std::cout << "Arrival: ";
                    printTime(train->getArrivalTime());
                    std::cout << " to platform " << train->getArrivalPlatform() << "\n";
                    std::cout << "Wagon ID: " << wagonId << "\n";
                    std::cout << "Seat: " << seatId << "\n";
                    std::cout << "Base Price: " << wagon->getStartingPrice() << "\n";
                    std::cout << "Final Price: " << finalPrice << "\n";
                    std::cout << "Ticket saved to: " << ticketFileName << "\n\n";
                }
                catch (const std::exception& e) 
                {
                    // освобождаване място?
                    std::cout << "Error: Failed to save ticket to file: " << e.what() << "\n";
                    std::cout << "Ticket purchase cancelled.\n";
                    continue;
                }
            }
            else if(command == "add-train")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }
                
                std::string startingStationName;
                std::string finalStationName;
                int speed;
                int distance;
                ss >> startingStationName >> finalStationName >> distance >> speed;
                TimePoint departureTime = parseTime(ss);
                Station * startingStation = stationRepo.findByName(startingStationName);
                Station * finalStation = stationRepo.findByName(finalStationName);

                if (!startingStation) 
                {
                    std::cout << "Error: No such station " << startingStationName << std::endl;
                    continue;
                }

                if (!finalStation) 
                {
                    std::cout << "Error: No such station " << finalStationName << std::endl;
                    continue;
                }

                Train* train = new Train();
                train->setFinalStation(finalStation);
                train->setStartingStation(startingStation);
                TimePoint arrivalTime = departureTime + std::chrono::minutes(int((distance/float(speed))*60));
                train->setDepartureTime(departureTime);
                train->setArrivalTime(arrivalTime);
                train->setSpeed(speed);
                train->setDistance(distance);

                // свободен коловоз в началната станция
                int departurePlatform = startingStation->getFreePlatform(departureTime);
                train->setDeparturePlatform(departurePlatform);
                
                // свободен коловоз в крайната станция
                int arrivalPlatform = finalStation->getFreePlatform(arrivalTime);
                train->setArrivalPlatform(arrivalPlatform);

                // добавям влака в станциите
                startingStation->addDepartingTrain(train);
                finalStation->addArrivingTrain(train);

                std::cout << "Train added successfully!" << std::endl;
                std::cout << "ID: " << train->getId() << std::endl;
                std::cout << "Departure: ";
                printTime(departureTime);
                std::cout << " from platform " << departurePlatform << std::endl;
                std::cout << "Arrival: ";
                printTime(arrivalTime);
                std::cout << " to platform " << arrivalPlatform << std::endl;

                printTime(departureTime);
                std::cout << std::endl;
                printTime(arrivalTime);
                std::cout << std::endl;
            }
            else if(command == "remove-train")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }
                
                int trainId;
                ss >> trainId;
                
                Train* train = stationRepo.findTrainById(trainId);

                if (!train) 
                {
                    std::cout << "Error: Train with ID " << trainId << " not found!\n";
                    continue;
                }
                
                std::cout << "Removing train " << trainId << ":\n";
                std::cout << "From: " << train->getStartingStation()->getStationName() << " (Platform " << train->getDeparturePlatform() << ") at ";
                printTime(train->getDepartureTime());
                std::cout << "\nTo: " << train->getFinalStation()->getStationName() << " (Platform " << train->getArrivalPlatform() << ") at ";
                printTime(train->getArrivalTime());
                std::cout << std::endl;
                
                // премахваме
                if (stationRepo.removeTrainById(trainId)) 
                {
                    std::cout << "Train " << trainId << " removed successfully!\n";
                } 
                else 
                {
                    std::cout << "Error: Failed to remove train " << trainId << "!\n";
                }
            }
            else if(command == "add-wagon")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }

                int trainId;
                std::string wagonType;
                double startingPrice;
                
                ss >> trainId >> wagonType >> startingPrice;
                
                Train* train = stationRepo.findTrainById(trainId);
                
                if (!train) 
                {
                    std::cout << "Error: Train with ID " << trainId << " not found!\n";
                    continue;
                }
                
                TimePoint currentTime = getCurrentTime();

                if(train->hasDeparted(currentTime))
                {
                    std::cout << "Error: Cannot add wagon to a train that has already departed!\n";
                    continue;
                }
                
                Wagon* wagon = nullptr;
                
                if (wagonType == "first-class" || wagonType == "1") 
                {
                    double comfortFactor;
                    std::string hasFood;
                    
                    ss >> comfortFactor >> hasFood;
                    
                    if (comfortFactor < 0.0 || comfortFactor > 1.0) 
                    {
                        std::cout << "Error: Comfort factor must be between 0.0 and 1.0!\n";
                        continue;
                    }
                    
                    bool includesFood = (hasFood == "yes" || hasFood == "true" || hasFood == "1");
                    
                    FirstClass* firstClassWagon = new FirstClass();
                    firstClassWagon->setStartingPrice(startingPrice);
                    firstClassWagon->setComfortFactor(comfortFactor);
                    firstClassWagon->setIncludesFood(includesFood);
                    firstClassWagon->setSeats(constants::SEATS_COUNT);
                    
                    wagon = firstClassWagon;
                    
                    std::cout << "Added first-class wagon to train " << trainId << std::endl;
                    std::cout << "Wagon ID: " << wagon->getId() << std::endl;
                    std::cout << "Starting Price: " << startingPrice << std::endl;
                    std::cout << "Comfort Factor: " << comfortFactor << std::endl;
                    std::cout << "Includes Food: " << (includesFood ? "Yes" : "No") << std::endl;
                    std::cout << firstClassWagon->ticketPrice() << std::endl;
                }
                else if (wagonType == "second-class" || wagonType == "2") 
                {
                    double pricePerKg;
                    int luggageKg;
                    
                    ss >> luggageKg >> pricePerKg;
                    
                    if (luggageKg < 0) 
                    {
                        std::cout << "Error: Luggage weight cannot be negative!\n";
                        continue;
                    }
                    
                    if (pricePerKg < 0) 
                    {
                        std::cout << "Error: Price per kg cannot be negative!\n";
                        continue;
                    }
                    
                    SecondClass* secondClassWagon = new SecondClass();
                    secondClassWagon->setStartingPrice(startingPrice);
                    secondClassWagon->setSeats(constants::SEATS_COUNT);
                    
                    wagon = secondClassWagon;
                    
                    std::cout << "Added second-class wagon to train " << trainId << std::endl;
                    std::cout << "Wagon ID: " << wagon->getId() << std::endl;
                    std::cout << "Starting Price: " << startingPrice << std::endl;
                    std::cout << "Luggage Weight: " << luggageKg << " kg" << std::endl;
                    std::cout << "Price per kg: " << pricePerKg << std::endl;
                    std::cout << secondClassWagon->ticketPrice() << std::endl;
                }
                else if (wagonType == "sleeping" || wagonType == "3") 
                {
                    double pricePer100Km;
                    
                    ss >> pricePer100Km;
                    
                    if (pricePer100Km < 0) 
                    {
                        std::cout << "Error: Price per 100km cannot be negative!\n";
                        continue;
                    }
                    
                    SleepingWagon* sleepingWagon = new SleepingWagon();
                    sleepingWagon->setStartingPrice(startingPrice);
                    sleepingWagon->setPricePer100Km(pricePer100Km);
                    sleepingWagon->setDistance(train->getDistance()); 
                    sleepingWagon->setSeats(constants::SEATS_COUNT);
                    
                    wagon = sleepingWagon;
                    
                    std::cout << "Added sleeping wagon to train " << trainId << std::endl;
                    std::cout << "Wagon ID: " << wagon->getId() << std::endl;
                    std::cout << "Starting Price: " << startingPrice << std::endl;
                    std::cout << "Price per 100km: " << pricePer100Km << std::endl;
                    std::cout << sleepingWagon->ticketPrice() << std::endl;
                }
                else 
                {
                    std::cout << "Error: Unknown wagon type '" << wagonType << "'!\n";
                    std::cout << "Available types: first-class, second-class, sleeping\n";
                    continue;
                }

                train->addWagon(wagon);
                std::cout << "Final ticket price: " << wagon->ticketPrice() << std::endl;
            }
            else if(command == "remove-wagon")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }

                int trainId;
                int wagonId;
                ss >> trainId >> wagonId;
                
                Train* train = stationRepo.findTrainById(trainId);

                if (!train) 
                {
                    std::cout << "Error: Train with ID " << trainId << " not found!\n";
                    continue;
                }

                TimePoint currentTime = getCurrentTime();

                if(train->hasDeparted(currentTime))
                {
                    std::cout << "Error: Cannot remove wagon from a train that has already departed!\n";
                    continue;
                }

                Wagon* wagon = train->getWagonByID(wagonId);

                if (!wagon)
                {
                    std::cout << "Error: Wagon with ID " << wagonId << " not found in train " << trainId << "!\n";
                    continue;
                }
                
                std::cout << "Removing wagon " << wagonId << " from train " << trainId << "...\n";
                std::cout << "Wagon ID: " << wagon->getId() << std::endl;
                std::cout << "Starting Price: " << wagon->getStartingPrice() << std::endl;
                std::cout << "Ticket Price: " << wagon->ticketPrice() << std::endl;
                
                train->removeWagon(wagonId);
                std::cout << "Wagon " << wagonId << " removed from train " << trainId << "!\n";
            }
            else if(command == "move-wagon")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }

                int sourceTrainId;
                int wagonId;
                int destinationTrainId;
                
                ss >> sourceTrainId >> wagonId >> destinationTrainId;
                
                Train* sourceTrain = stationRepo.findTrainById(sourceTrainId);
                if (!sourceTrain) 
                {
                    std::cout << "Error: Source train with ID " << sourceTrainId << " not found!\n";
                    continue;
                }
                
                Train* destinationTrain = stationRepo.findTrainById(destinationTrainId);
                if (!destinationTrain) 
                {
                    std::cout << "Error: Destination train with ID " << destinationTrainId << " not found!\n";
                    continue;
                }
                
                if (sourceTrainId == destinationTrainId) 
                {
                    std::cout << "Error: Source and destination trains cannot be the same!\n";
                    continue;
                }
                
                TimePoint currentTime = getCurrentTime();

                if (sourceTrain->hasDeparted(currentTime)) 
                {
                    std::cout << "Error: Cannot move wagon from a train that has already departed!\n";
                    continue;
                }
                
                if (destinationTrain->hasDeparted(currentTime)) 
                {
                    std::cout << "Error: Cannot move wagon to a train that has already departed!\n";
                    continue;
                }
                
                Wagon* wagon = sourceTrain->getWagonByID(wagonId);
                if (!wagon) 
                {
                    std::cout << "Error: Wagon with ID " << wagonId << " not found in source train " << sourceTrainId << "!\n";
                    continue;
                }
                
                if (wagon->hasBookedSeats()) 
                {
                    std::cout << "Error: Cannot move wagon with booked tickets!\n";
                    continue;
                }
                
                std::cout << "Moving wagon " << wagonId << " from train " << sourceTrainId << " to train " << destinationTrainId << "...\n";
                std::cout << "Wagon ID: " << wagon->getId() << std::endl;
                std::cout << "Starting Price: " << wagon->getStartingPrice() << std::endl;
                std::cout << "Ticket Price: " << wagon->ticketPrice() << std::endl;
                
                sourceTrain->removeWagonKeepObject(wagonId);
                
                destinationTrain->addWagon(wagon);
                
                std::cout << "Wagon " << wagonId << " successfully moved from train " << sourceTrainId << " to train " << destinationTrainId << "!\n";
                std::cout << "New ticket price: " << wagon->ticketPrice() << std::endl;
            }
            else if(command == "create-discount-card")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }
                
                std::string cardType;
                std::string userName;
                std::string fileName;
                
                ss >> cardType >> userName >> fileName;
                
                if (cardType.empty() || userName.empty() || fileName.empty()) 
                {
                    std::cout << "Error: Give card type, user name, and file name!\n";
                    std::cout << "Card types: age, distance, route\n";
                    continue;
                }
                
                try {
                    if (cardType == "age") 
                    {
                        int age;
                        ss >> age;
                        
                        if (!ss) 
                        {
                            std::cout << "Error: Please give age for age card!\n\n";
                            continue;
                        }
                        
                        AgeCard ageCard(userName, age);
                        ageCard.saveToFile(fileName);
                        
                        std::cout << "Age discount card created successfully!\n";
                        std::cout << "Card ID: " << ageCard.getID() << "\n";
                        std::cout << "Card Holder: " << ageCard.getCardHolderName() << "\n";
                        std::cout << "Age: " << ageCard.getCardHoldersAge() << "\n";
                        std::cout << "Discount: " << ageCard.getDiscountPercentage() << "%\n";
                        std::cout << "Card saved to: " << fileName << "\n\n";
                    }
                    else if (cardType == "distance") 
                    {
                        double maxDistance;
                        ss >> maxDistance;
                        
                        if (!ss || maxDistance <= 0) 
                        {
                            std::cout << "Error: Please give valid max distance for distance card!\n\n";
                            continue;
                        }
                        
                        DistanceCard distanceCard(userName, maxDistance);
                        distanceCard.saveToFile(fileName);
                        
                        std::cout << "Distance discount card created successfully!\n";
                        std::cout << "Card ID: " << distanceCard.getID() << "\n";
                        std::cout << "Card Holder: " << distanceCard.getCardHolderName() << "\n";
                        std::cout << "Max Distance: " << distanceCard.getMaxDistance() << " km\n";
                        std::cout << "Short Distance Discount: 50%\n";
                        std::cout << "Long Distance Discount: 30%\n";
                        std::cout << "Card saved to: " << fileName << "\n\n";
                    }
                    else if (cardType == "route") 
                    {
                        std::string destination;
                        ss >> destination;
                        
                        if (destination.empty()) 
                        {
                            std::cout << "Error: Please give destination for route card!\n\n";
                            continue;
                        }
                        
                        RouteCard routeCard(userName, destination);
                        routeCard.saveToFile(fileName);
                        
                        std::cout << "Route discount card created successfully!\n";
                        std::cout << "Card ID: " << routeCard.getID() << "\n";
                        std::cout << "Card Holder: " << routeCard.getCardHolderName() << "\n";
                        std::cout << "Destination: " << routeCard.getDestination() << "\n";
                        std::cout << "Discount: " << routeCard.getDiscountPercentage() << "%\n";
                        std::cout << "Card saved to: " << fileName << "\n\n";
                    }
                    else 
                    {
                        std::cout << "Error: Unknown card type '" << cardType << "'!\n";
                        std::cout << "Available types: age, distance, route\n";
                    }
                }
                catch (const std::exception& e) 
                {
                    std::cout << "Error: Failed to create discount card: " << e.what() << "\n";
                }
            }
            else if(command == "exit")
            {
                std::cout << "Bye.\n";
                break;
            }
            else
            {
                std::cout << "Command not found! Try again.\n";
            }

        }
    }

    Application()
    {
        adminRepo.addAdmin("tedi", "123");
    };

    ~Application()
    {
        
    };

private:

    AdminRepo adminRepo;
    StationsRepo stationRepo;
    bool isAdmin;
    
};
