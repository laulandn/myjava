
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


#include "Long.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  Long Class
////////////////////////////////////////////////////////////////////////////////

Long::Long(long i)
{
  theLongVal=i;
}


Long::Long(NJString s)
{
  // TO BE DONE
  theLongVal=0;
}


NJString Long::toString()
{
  // TO BE DONE
  return NULL;
}

