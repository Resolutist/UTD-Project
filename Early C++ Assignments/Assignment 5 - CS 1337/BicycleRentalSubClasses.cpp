#ifndef FILE_BICYCLE_RENTAL_SUBCLASSES_CPP
#define FILE_BICYCLE_RENTAL_SUBCLASSES_CPP
#include <iostream>
#include <iomanip>
#include "BicycleTypes.h"
#include "BicycleRentalClass.h"
#include "BicycleRentalSubClasses.h"

//Standard -----------------------------------

BicycleRentalStandardClass::BicycleRentalStandardClass(unsigned bicycleId) :
    BicycleRentalClass(bicycleId, BICYCLE_TYPE::STANDARD, BICYCLE_TYPE_STRING[(unsigned)BICYCLE_TYPE::STANDARD],
      BICYCLE_TYPE_RENTAL_RATES[(unsigned)BICYCLE_TYPE::STANDARD]) {
  }// BicycleRentalStandardClass

// Returns the total rental cost based, updates counters
  void BicycleRentalStandardClass::calculateRentalFees(unsigned daysToRent) {
    float rentCharge = getBicycleTypeRentalRate() * daysToRent;
    setBicycleTypeDaysToRent(daysToRent);
    setBicycleTypeCharge(rentCharge);
    setTotalNoBikesPerTypeRented();
    setTotalSalesPerBikeTypeRented(rentCharge);

    setTotalNoBikesRented();
    setTotalSalesAllBikesRented(rentCharge);
  }

  void BicycleRentalStandardClass::displayBikeRentalInformation() {
    cout.precision(2); cout << fixed;
    cout <<
      "Bike Rental Information" << endl <<
      "-----------------------" << endl <<
      "Bike Id           : " << getBicycleId() << endl <<
      "Bicycle Type      : " << getBicycleTypeStr() << endl <<
      "Rental Day(s)     : " << getBicycleTypeDaysToRent() << endl <<
      "Daily Rental Rate : " << getBicycleTypeRentalRate() << endl <<
      "Rental Charge     : " << getBicycleTypeCharge() << endl << endl <<

      "Totals: " << endl <<
      "------- " << endl <<
      "Number of Bike Type Rented    : " << getTotalNoBikesPerTypeRented() << endl <<
      "Sales Amount Bike Type Rented : " << getTotalSalesPerBikeTypeRented() << endl << endl <<
      "Total Number of Bikes Rented  : " << getTotalNoBikesRented() << endl <<
      "Total Sales All Bikes Rented  : " << getTotalSalesAllBikesRented() << endl << endl <<

      "Press the enter key to continue." << endl << endl;
    cin.ignore(); cin.get();
  }

//Racer-----------------------------------------

BicycleRentalRacerClass::BicycleRentalRacerClass(unsigned bicycleId)
  : BicycleRentalClass(bicycleId, BICYCLE_TYPE::RACER, BICYCLE_TYPE_STRING[(unsigned)BICYCLE_TYPE::RACER],
                                  BICYCLE_TYPE_RENTAL_RATES[(unsigned)BICYCLE_TYPE::RACER]) {
}// BicycleRentalRacerClass

// Returns the total rental cost based, updates counters
void BicycleRentalRacerClass::calculateRentalFees(unsigned daysToRent) {
    float rentCharge = getBicycleTypeRentalRate() * daysToRent;
    setBicycleTypeDaysToRent(daysToRent);
    setBicycleTypeCharge(rentCharge);
    setTotalNoBikesPerTypeRented();
    setTotalSalesPerBikeTypeRented(rentCharge);

    setTotalNoBikesRented();
    setTotalSalesAllBikesRented(rentCharge);
}

void BicycleRentalRacerClass::displayBikeRentalInformation() {
    cout.precision(2); cout << fixed;
    cout <<
      "Bike Rental Information" << endl <<
      "-----------------------" << endl <<
      "Bike Id           : " << getBicycleId() << endl <<
      "Bicycle Type      : " << getBicycleTypeStr() << endl <<
      "Rental Day(s)     : " << getBicycleTypeDaysToRent() << endl <<
      "Daily Rental Rate : " << getBicycleTypeRentalRate() << endl <<
      "Rental Charge     : " << getBicycleTypeCharge() << endl << endl <<

      "Totals: " << endl <<
      "------- " << endl <<
      "Number of Bike Type Rented    : " << getTotalNoBikesPerTypeRented() << endl <<
      "Sales Amount Bike Type Rented : " << getTotalSalesPerBikeTypeRented() << endl << endl <<
      "Total Number of Bikes Rented  : " << getTotalNoBikesRented() << endl <<
      "Total Sales All Bikes Rented  : " << getTotalSalesAllBikesRented() << endl << endl <<

      "Press the enter key to continue." << endl << endl;
    cin.ignore(); cin.get();

}

//BMX --------------------------------------------

BicycleRentalBMXClass::BicycleRentalBMXClass(unsigned bicycleId)
    : BicycleRentalClass(bicycleId, BICYCLE_TYPE::BMX, BICYCLE_TYPE_STRING[(unsigned)BICYCLE_TYPE::BMX],
      BICYCLE_TYPE_RENTAL_RATES[(unsigned)BICYCLE_TYPE::BMX]) {
  }// BicycleRentalStandardClass

// Returns the total rental cost based, updates counters
void BicycleRentalBMXClass::calculateRentalFees(unsigned daysToRent) {
    float rentCharge = getBicycleTypeRentalRate() * daysToRent;
    setBicycleTypeDaysToRent(daysToRent);
    setBicycleTypeCharge(rentCharge);
    setTotalNoBikesPerTypeRented();
    setTotalSalesPerBikeTypeRented(rentCharge);

    setTotalNoBikesRented();
    setTotalSalesAllBikesRented(rentCharge);
}

void BicycleRentalBMXClass::displayBikeRentalInformation() {
    cout.precision(2); cout << fixed;
    cout <<
      "Bike Rental Information" << endl <<
      "-----------------------" << endl <<
      "Bike Id           : " << getBicycleId() << endl <<
      "Bicycle Type      : " << getBicycleTypeStr() << endl <<
      "Rental Day(s)     : " << getBicycleTypeDaysToRent() << endl <<
      "Daily Rental Rate : " << getBicycleTypeRentalRate() << endl <<
      "Rental Charge     : " << getBicycleTypeCharge() << endl << endl <<

      "Totals: " << endl <<
      "------- " << endl <<
      "Number of Bike Type Rented    : " << getTotalNoBikesPerTypeRented() << endl <<
      "Sales Amount Bike Type Rented : " << getTotalSalesPerBikeTypeRented() << endl << endl <<
      "Total Number of Bikes Rented  : " << getTotalNoBikesRented() << endl <<
      "Total Sales All Bikes Rented  : " << getTotalSalesAllBikesRented() << endl << endl <<

      "Press the enter key to continue." << endl << endl;
    cin.ignore(); cin.get();

}

#endif
