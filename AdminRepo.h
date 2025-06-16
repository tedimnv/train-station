#pragma once
#include <vector>
#include "Admin.h"

class AdminRepo
{
public:

    void addAdmin(std::string username, std::string password);
    bool exists(std::string username, std::string password);

private:

    std::vector<Admin> admins;
};
