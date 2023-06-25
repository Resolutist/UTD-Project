//This program tracks the activity of 3 hot dog stands.
//CS 1337 Assignment 4
//10/26/20
//By: Kyle White
//10/22/20 Adjusted code to include cost of each hot dog.
//10/26/20 Fixed the unsigned value of the appropriate hot dog header and prototype.
//10/26/20 Was not able to compile and link each file together until the correct gnu compiler was used.
#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>

#include "HotDogStandClass.h"

using namespace std;

//Operator overload to display the object's table of contents.
//Pass hot dog object by reference and set it to a constant value, so it won't be modified.
ostream& operator << (ostream& leftSideOutputStream, const HotDogStandClass& hotDogStandObj)
{
    //Parameter.
    leftSideOutputStream <<
    //Add all headers to said parameter.
        "Stand Id: " + hotDogStandObj.getId() << endl <<
        "Location: " + hotDogStandObj.getLocation() << endl <<
        "Inventory: " << hotDogStandObj.getInventoryCount() << endl <<
        "Store Sold: " << hotDogStandObj.getSoldCount() << " at $" << hotDogStandObj.getCost() << " each." << endl;
        "Global Sold: " << HotDogStandClass::getGlobalSalesCount() << endl << endl;
    return leftSideOutputStream;
}

int main()
{
    //Output formatting.
    cout << setprecision(2) << fixed << showpoint;
    //Constructors
    HotDogStandClass hotDogStand1("1-TX-Plano", "1332 S Plano Rd", 8.9f, 3);
    HotDogStandClass hotDogStand2("2-TX-Custer", "3411 Custer Parkway", 15.1f, 3);
    HotDogStandClass hotDogStand3("3-TX-Abrams", "891 Abrams Rd", 5.6f, 3);

    cout << "Initial states of the stands:" << endl << endl;
    //Checks if the output stream is working correctly.
    cout << hotDogStand1 << endl;
    cout << hotDogStand2 << endl;
    cout << hotDogStand3 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    //Test adding and subtracting from inventory.
    cout << "Add 2 hot dogs to hot dog stand 2's inventory" << endl;
    hotDogStand2.stockInventory(2);
    cout << hotDogStand1 << endl << endl;

    cout << "Subtract 2 hot dogs to hot dog stand 2's inventory" << endl;
    hotDogStand2.stockInventory(-2);
    cout << hotDogStand1 << endl;

    //Track hot dog stands through each form of purchase and situation.
    cout << "Test normal purchases: " << endl << endl;

    cout << "Buy 4 hot dogs from the 1st Hot Dog Stand" << endl;
    hotDogStand1.hotDogsBuy(4);
    cout << hotDogStand1 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    cout << "Buy 3 hot dogs from the 3rd Hot Dog Stand" << endl;
    hotDogStand3.hotDogsBuy(3);
    cout << hotDogStand3 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    cout << "Test purchase greater than inventory from the 1st Hot Dog Stand" << endl;
    cout << "Buy 5 hot dogs from the 1st Hot Dog Stand" << endl;
    hotDogStand1.hotDogsBuy(5);
    cout << hotDogStand1 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    cout << "Test purchase when no hot dogs left from the 3rd Hot Dog Stand" << endl;
    cout << "Buy 1 hot dog from the 3rd Hot Dog Stand" << endl;
    hotDogStand3.hotDogsBuy(1);
    cout << hotDogStand3 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    cout << "Test purchase when one hot dog is left " << endl;
    cout << "Buy 1 hot dog from the first Hot Dog Stand" << endl;
    hotDogStand1.hotDogsBuy(1);
    cout << hotDogStand1 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    cout << "Test negative purchase count " << endl;
    cout << "Buy 1 hot dog from the 3rd Hot Dog Stand" << endl;
    hotDogStand3.hotDogsBuy(-2);
    cout << hotDogStand3 << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    cout << "Final states of the stands" << endl << endl;
    cout << hotDogStand1 << endl;
    cout << hotDogStand2 << endl;
    cout << hotDogStand3 << endl;

    cout << "Come again!" << endl;

    cout << "Please press enter to continue."; cin.ignore(); cin.get();

    return 0;
}
