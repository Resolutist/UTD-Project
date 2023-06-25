#ifndef FILE_BICYCLE_RENTAL_CLASS_CPP
#define FILE_BICYCLE_RENTAL_CLASS_CPP
#include "BicycleTypes.h"
#include "BicycleRentalClass.h"

// Accessor and mutator methods
  unsigned     BicycleRentalClass::getBicycleId()                   { return this->bicycleId; }
  BICYCLE_TYPE BicycleRentalClass::getBicycleType()                 { return this->bicycleType; }
  string       BicycleRentalClass::getBicycleTypeStr()              { return this->bicycleTypeString; }
  unsigned     BicycleRentalClass::getBicycleTypeDaysToRent()       { return this->bicycleTypeDaysToRent; }
  float        BicycleRentalClass::getBicycleTypeRentalRate()       { return this->bicycleTypeRentalRate; }
  float        BicycleRentalClass::getBicycleTypeCharge()           { return this->bicycleTypeCharge; }

  unsigned     BicycleRentalClass::getTotalNoBikesPerTypeRented()   { return this ->totalNoBikesTypeRented; }
  float        BicycleRentalClass::getTotalSalesPerBikeTypeRented() { return this->totalSalesBikeTypeRented; }
  unsigned     BicycleRentalClass::getTotalNoBikesRented()          { return this->totalNoBikesRented; }
  float        BicycleRentalClass::getTotalSalesAllBikesRented()    { return this->totalSalesAllBikesRented; }

  void BicycleRentalClass::setBicycleTypeDaysToRent(unsigned bicycleTypeDaysToRent) { this->bicycleTypeDaysToRent = bicycleTypeDaysToRent; }
  void BicycleRentalClass::setBicycleTypeCharge(float bicycleTypeCharge)            { this->bicycleTypeCharge = bicycleTypeCharge; }
  void BicycleRentalClass::setTotalNoBikesRented         () { (this->totalNoBikesRented)++;     }
  void BicycleRentalClass::setTotalNoBikesPerTypeRented  () { (this->totalNoBikesTypeRented)++; }
  void BicycleRentalClass::setTotalSalesPerBikeTypeRented(float totalSalesPerBikeTypeRented)
                                                            { this->totalSalesBikeTypeRented += totalSalesPerBikeTypeRented;}
  void BicycleRentalClass::setTotalSalesAllBikesRented   (float totalSalesAllBikesRented)
                                                            { this->totalSalesAllBikesRented += totalSalesAllBikesRented;  }


  // Constructors
  BicycleRentalClass::BicycleRentalClass(unsigned bicycleId=0,  BICYCLE_TYPE bicycleType=BICYCLE_TYPE::STANDARD,
                                         string   bicycleTypeStr= BICYCLE_TYPE_STRING[(unsigned)BICYCLE_TYPE::STANDARD],
                                         float    bicycleTypeRentalRate=0.0) {
    this->bicycleId = bicycleId;
    this->bicycleType = bicycleType;
    this->bicycleTypeString = bicycleTypeStr;
    this->bicycleTypeRentalRate = bicycleTypeRentalRate;
  };// BicycleRentalClass

  // Checks if Objects are the same
  bool BicycleRentalClass::equals(BicycleRentalClass *otherBicycleRentalClassObj) {
    if(otherBicycleRentalClassObj->getBicycleId() != this->getBicycleId())
      return false;
    return true;
  }//equals()

  // initialize statics in BicycleRentalClass
  unsigned BicycleRentalClass::totalNoBikesRented          = 0;
  float    BicycleRentalClass::totalSalesAllBikesRented    = 0;

#endif
