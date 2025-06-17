#pragma once

class DiscountCard //abstract
{
  
private:
    std::string cardHolderName;
    std::string classType;
    int ID; //6 digits
    int discountPercentage;
    
    virtual void copyFrom(const DiscountCard& other) {}
    virtual void moveFrom(DiscountCard&& other) {}
    virtual void free() {}

protected:
    void setCardHolder(const std::string& name) 
    {
        cardHolderName = name;
    }
    
    void generateID() 
    {
    
        srand(time(0)); 
        ID = rand() % 900000 + 100000;
    }

public:
    DiscountCard() : discountPercentage(0), ID(0) {}
    virtual ~DiscountCard() = default;
    
    void setDiscountPercentage(int percentage) 
    {
        discountPercentage = percentage;
    }
    
    int getID() const { return ID; }
    std::string getCardHolderName() const 
    { 
        return cardHolderName; 
    }
    
    int getDiscountPercentage() const 
    { 
        return discountPercentage;
    }

    std::string getClassType() const 
    { 
        return classType; 
    }
    
    virtual void setDiscount() = 0;
    virtual bool isApplicable(const std::string& route = "", double distance = 0) const = 0;
    virtual void saveToFile(const std::string& fileName) const = 0;
    
protected:
    void setClassType(const std::string& type) 
    { 
        classType = type; 
    }

};
