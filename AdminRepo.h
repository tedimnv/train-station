#pragma once
#include <vector>
#include "Admin.h"

class AdminRepo
{
public:

    void addAdmin(std::string username, std::string password)
    {
        admins.push_back(Admin(username, password));
    }

    bool exists(std::string username, std::string password)
    {
        Admin admin(username, password);
        
        for(int i = 0; i < admins.size(); i++)
        {
            if(admins[i] == admin)
                return true;
        }    

        return false;
    }


private:

    std::vector<Admin> admins;

};
