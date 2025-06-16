#pragma once
#include "AdminRepo.h"
#include "StationsRepo.h"
#include "TrainRepo.h"
#include <sstream>
#include "Time.h"


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
