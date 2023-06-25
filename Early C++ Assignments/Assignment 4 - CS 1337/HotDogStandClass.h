#ifndef HOT_DOG_STAND_CLASS_H
#define HOT_DOG_STAND_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

class HotDogStandClass
{
//Set private parameters to each HotDogStandObj.
private:

    string id;
    string location;
    float cost;
    unsigned inventoryCount; //Inventory and sold count should always be greater than zero, so they are made unsigned.
    unsigned soldCount;
    //Make global count private so that each object can share it, and it also prevents collusion.
    static unsigned globalSalesCount;

public:

//Function Prototypes
void HotDogStandClass::hotDogsBuy(int count);
void stockInventory(int stockCount);

    //Default Constructor
    HotDogStandClass(string const &id, string const &location, float cost)
    //Function Call.
    : HotDogStandClass(id, location, cost, 0) {}
    //Main Constructor
    HotDogStandClass(string const &id, string const &location, float cost, unsigned inventoryCount)
    {
        //Call the private parameters, which allows us to use the same name as a pointer instead of a reference.
        this->id = id;
        this->location = location;
        this->cost = cost;
        this->inventoryCount = inventoryCount;
        //Initialize the number of hot dogs sold to 0 per Hot dog class.
        this->soldCount = 0;
    }
    //Getters and Setters for all private member instance variables.
    const string &getId() const {return id;}
    void setId(const string &id) {HotDogStandClass::id = id;}

    const string &getLocation() const {return location;}
    void setLocation(const string &location) {HotDogStandClass::location = location;}

    float getCost() const {return cost;}
    void setCost(float cost) {HotDogStandClass::cost = cost;}

    unsigned getSoldCount() const {return soldCount;}
    unsigned getInventoryCount() const {return inventoryCount;}
    static unsigned getGlobalSalesCount() {return HotDogStandClass::globalSalesCount; }

};//HotDogStandClass End Brace.

#endif // HOT_DOG_STAND_CLASS_H
