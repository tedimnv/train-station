#include <iostream>
#include <cstdlib>
#include <ctime>
#include "User.h"
#include "Admin.h"


int main() 
{
    std::cout << "Choose one from these commands: " << std::endl;
    std::cout << "1. Print stations " << std::endl;
    std::cout << "2. Print schedule " << std::endl;
    std::cout << "3. Print schedule destination " << std::endl;
    std::cout << "4. Print schedule time " << std::endl;
    std::cout << "5. Print train " << std::endl;
    std::cout << "6. Print wagon " << std::endl;
    std::cout << "7. Buy ticket " << std::endl;
    std::cout << "8. Buy ticket with discount " << std::endl;
    std::cout << "9. Add station (Admin command) " << std::endl;
    std::cout << "10. Add train (Admin command) " << std::endl;
    std::cout << "11. Remove train (Admin command) " << std::endl;
    std::cout << "12. Add wagon (Admin command) " << std::endl;
    std::cout << "13. Move wagon (Admin command) " << std::endl;
    std::cout << "14. Create discount card (Admin command) " << std::endl;
    std::cout << "15. Validate discount card (Admin command) " << std::endl;

    int commandNumber;

    std::cin >> commandNumber;

    if(commandNumber == 1)
        User::printStations();
    else if(commandNumber == 2)
        User::printSchedule();
    else if(commandNumber == 3)
        std::cout << "3. Print schedule destination " << std::endl;
    else if(commandNumber == 4)
        std::cout << "4. Print schedule time " << std::endl;
    else if(commandNumber == 5)
        std::cout << "5. Print train " << std::endl;
    else if(commandNumber == 6)
        std::cout << "6. Print wagon " << std::endl;
    else if(commandNumber == 7)
        std::cout << "7. Buy ticket " << std::endl;
    else if(commandNumber == 8)
        std::cout << "8. Buy ticket with discount " << std::endl;
    else if(commandNumber == 9)
        std::cout << "9. Add station (Admin command) " << std::endl;
    else if(commandNumber == 10)
        std::cout << "10. Add train (Admin command) " << std::endl;
    else if(commandNumber == 11)
        std::cout << "11. Remove train (Admin command) " << std::endl;
    else if(commandNumber == 12)
        std::cout << "12. Add wagon (Admin command) " << std::endl;
    else if(commandNumber == 13)
        std::cout << "13. Move wagon (Admin command) " << std::endl;
    else if(commandNumber == 14)
        std::cout << "14. Create discount card (Admin command) " << std::endl;
    else if(commandNumber == 15)
        std::cout << "15. Validate discount card (Admin command) " << std::endl;
    

}
