#ifndef FILE_BICYCLE_RENTAL_CLASS_H_
#define FILE_BICYCLE_RENTAL_CLASS_H_
#include "BicycleTypes.h"

class  BicycleRentalClass {

private:
  unsigned        bicycleId;
  BICYCLE_TYPE    bicycleType;
  string          bicycleTypeString;
  unsigned        bicycleTypeDaysToRent;
  float           bicycleTypeRentalRate;
  float           bicycleTypeCharge;
  unsigned        totalNoBikesTypeRented   = 0;
  float           totalSalesBikeTypeRented = 0;

  static unsigned totalNoBikesRented;
  static float    totalSalesAllBikesRented;

  // Accessor and mutator methods
public:
  unsigned     getBicycleId();
  BICYCLE_TYPE getBicycleType();
  string       getBicycleTypeStr();
  unsigned     getBicycleTypeDaysToRent();
  float        getBicycleTypeRentalRate();
  float        getBicycleTypeCharge();
  unsigned     getTotalNoBikesPerTypeRented();
  float        getTotalSalesPerBikeTypeRented();

  unsigned     getTotalNoBikesRented();
  float        getTotalSalesAllBikesRented();

  void         setBicycleTypeDaysToRent(unsigned);
  void         setBicycleTypeCharge(float);
  void         setTotalSalesPerBikeTypeRented(float totalSalesPerBikeType);
  void         setTotalNoBikesPerTypeRented();

  void         setTotalNoBikesRented       ();
  void         setTotalSalesAllBikesRented (float totalSalesAllBikesRented);

public:
  // Constructors
//  BicycleRentalClass();
  BicycleRentalClass(unsigned bicycleId, BICYCLE_TYPE bicycleType, string bicycleTypeStr, float bicycleTypeRentalRate);

  // Define equals where the ID's match
  bool equals(BicycleRentalClass *otherBicycleRentalClassObj);

  //calculate Rental Fees Fees returns the rental cost in rental fee
  virtual void calculateRentalFees(unsigned daysToRent) = 0;

  // display Bike Rental Information
  virtual void displayBikeRentalInformation() = 0;

}; // BicycleRentalClass

#endif
