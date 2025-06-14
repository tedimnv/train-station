#pragma once

class DiscountCard //abstract
{
    std::string name;
    int ID; //6 цифри 
    
public:
    int discountPercentage;
    void setDiscountPercentage(int percentage);
    void getID(int id);
    void isApplicable();
};
