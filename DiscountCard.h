#pragma once

class DiscountCard
{
    // име без string!!
    int ID; //6 цифри randomizer
    int discountPercentage;
    
public:
    void setDiscountPercentage(int percentage);
    void getID(int id);
    void isApplicable();
};
