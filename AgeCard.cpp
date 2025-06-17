#include <iostream>
#include <fstream>
#include "AgeCard.h"


    namespace constants
{
    const int CHILD_DISCOUNT = 100;    //  1-10: 100% 
    const int STUDENT_DISCOUNT = 50;   //  11-18: 50%   
    const int ADULT_DISCOUNT = 20;     //  19+: 20% 
}


AgeCard::AgeCard(const std::string& name, int age) : cardHolderAge(0)
{
    setCardHolder(name);
    setClassType("AgeCard");
    generateID();
    setAge(age);
    setDiscount();
}

void AgeCard::setAge(int age)
{
    if (age < 1) {
        this->cardHolderAge = 1;
        std::cout << "Warning: Age should be a positive number. Setting to 1." << std::endl;
    } else {
        this->cardHolderAge = age;
    }
}

void AgeCard::setDiscount()
{
    int percentage = 0;

    if (cardHolderAge >= 1 && cardHolderAge <= 10)
        percentage = constants::CHILD_DISCOUNT;
    else if (cardHolderAge >= 11 && cardHolderAge <= 18)
        percentage = constants::STUDENT_DISCOUNT;
    else
        percentage = constants::ADULT_DISCOUNT;

    setDiscountPercentage(percentage);
}

bool AgeCard::isApplicable(const std::string& route, double distance) const
{
    return true; // Age cards are always applicable
}

void AgeCard::saveToFile(const std::string& fileName) const
{
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    
    file << "=== DISCOUNT CARD ===" << std::endl;
    file << "Card Type: " << getClassType() << std::endl;
    file << "Card ID: " << getID() << std::endl;
    file << "Card Holder: " << getCardHolderName() << std::endl;
    file << "Age: " << cardHolderAge << std::endl;
    file << "Discount: " << getDiscountPercentage() << "%" << std::endl;
    file << "=====================" << std::endl;
    
    file.close();
}
