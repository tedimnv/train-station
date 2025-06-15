#pragma once

class DiscountCard //abstract
{
    std::string cardHolderName;
    std::string classsType;
    int ID; //6 цифри 
    
    virtual void copyFrom(const DiscountCard& other);
	virtual void moveFrom(DiscountCard&& other)
    {

    }
	virtual void free()
    {

    }

	void setCardHolder(std::string name)
    {

    }
	void setID()
    {
        
    }

public:
    int discountPercentage;
    void setDiscountPercentage(int percentage);
    void getID(int id);
    void isApplicable();
};
