
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


#include "Integer.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  Integer Class
////////////////////////////////////////////////////////////////////////////////

Integer::Integer(int i)
{
  theIntegerVal=i;
}


/*
Integer::Integer(String *s)
{
  // TO BE DONE
  theIntegerVal=0;
}
*/


Integer::Integer(NJString s)
{
  // TO BE DONE
  theIntegerVal=0;
}


NJString Integer::toString()
{
  // TO BE DONE
  return NULL;
}

