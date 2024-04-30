
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#define _USE_MATH_DEFINES 1


#include "MyMath.h"


#include <math.h>



////////////////////////////////////////////////////////////////////////////////
//  Math global funcs
////////////////////////////////////////////////////////////////////////////////

double Math_pow(double a,double b)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Math_pow()\n";
#endif // DEBUG_VERBOSE
  return pow(a,b);
}


