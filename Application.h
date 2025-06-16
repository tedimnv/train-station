#pragma once
#include "AdminRepo.h"
#include "StationsRepo.h"
#include "TrainRepo.h"
#include <sstream>
#include "Time.h"
#include "FirstClass.h"
#include "SecondClass.h"
#include "SleepingWagon.h"
#include "Wagon.h"



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
                
                // проверявам дали съществува влака
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
                
                // Намираме влака по ID
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
                    //secondClassWagon->setLuggageKg(luggageKg);
                    //secondClassWagon->setPricePerKg(pricePerKg);
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
                
                // Remove the wagon from the train
                train->removeWagon(wagonId);
                std::cout << "Wagon " << wagonId << " removed from train " << trainId << "!\n";
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
