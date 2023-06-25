#ifndef FILE_BICYCLE_SUBCLASSES_H_
#define FILE_BICYCLE_SUBCLASSES_H_
#include "BicycleTypes.h"
#include "BicycleRentalClass.h"

// The BicycleRentalStandardClass class inherits the BicycleRentalStandardClass
class BicycleRentalStandardClass : public BicycleRentalClass {
public:
  //Constructors
  BicycleRentalStandardClass(unsigned bicycleId);

  // Returns the total rental cost based, updates counters
  void calculateRentalFees(unsigned daysToRent);

  // display Bike Rental Information
  void displayBikeRentalInformation();

}; // BicycleRentalStandardClass

// The BicycleRentalRacerClass class extends the BicycleRentalClass
class BicycleRentalRacerClass : public BicycleRentalClass {
public:
  //Constructors
  BicycleRentalRacerClass(unsigned bicycleId);

  // Returns the total rental cost based, updates counters
  void calculateRentalFees(unsigned daysToRent);

  void displayBikeRentalInformation();

}; // BicycleRentalRacerClass

// The BicycleRentalBMXClass class inherits from the BicycleRentalClass
class BicycleRentalBMXClass : public BicycleRentalClass {
public:
  //Constructors
  BicycleRentalBMXClass(unsigned bicycleId);

  // Returns the total rental cost based, updates counters
  void calculateRentalFees(unsigned daysToRent);

  void displayBikeRentalInformation();

}; // BicycleRentalBMXClass


#endif
