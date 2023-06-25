#ifndef FILE_BICYCLE_TYPES_H_
#define FILE_BICYCLE_TYPES_H_

#include<string>
using namespace std;

enum   class        BICYCLE_TYPE                  {  STANDARD,   RACER,   BMX, NOOFBIKETYPES };
static string const BICYCLE_TYPE_STRING[]       = { "Standard", "Racer", "BMX" };
static float  const BICYCLE_TYPE_RENTAL_RATES[] = {  1.00f,      1.50f,   1.89f };

#endif
