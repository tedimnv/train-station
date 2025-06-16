#include <iostream>
#include "AdminRepo.h"

void AdminRepo::addAdmin(std::string username, std::string password)
{
    admins.push_back(Admin(username, password));
}

bool AdminRepo::exists(std::string username, std::string password)
{
    Admin admin(username, password);
        
        for(int i = 0; i < admins.size(); i++)
        {
            if(admins[i] == admin)
                return true;
        }    

        return false;
}
