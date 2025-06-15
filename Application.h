#pragma once
#include "AdminRepo.h"
#include "StationsRepo.h"
#include "TrainRepo.h"
#include <sstream>

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

            if(command == "add-station")
            {
                if(!isAdmin)
                {
                    std::cout << "Error: You need to be an administrator to run this command!\n";
                    continue;
                }

                std::string name;

                ss >> name;

                stationRepo.addStation(name);
            }

            if(command == "print-stations")
            {
                const std::vector <Station>& stations = stationRepo.getAll();
                for ( size_t i = 0 ; i < stations.size() ; i++) 
                {
                    std::cout << stations[i].getStationName() << std::endl;
                }
            }

            if(command == "add-train")
            {
                std::string startingStationName;
                std::string finalStationName;
                std::string departureTime;
                std::string departureDate;
                int speed;
                int distance;
                ss >> startingStationName >> finalStationName >> distance >> speed >> departureDate >> departureTime;
                Station * startingStation = stationRepo.findByName(startingStationName);
                Station * finalStation = stationRepo.findByName(finalStation);
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
                Train train;
                std::mt arrivalTime = {};
                std::mt departureTime = {};
                
                train.distance = distance;
                startingStation->addTrain(train);
                finalStation->addArrivingTrain();
            }

            if(command == "exit")
            {
                std::cout << "Bye.\n";
                break;
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
