
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr
#define ERR_OUT std::cerr


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "Byte.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  Byte Class
////////////////////////////////////////////////////////////////////////////////

Byte::Byte(jbyte i)
{
  theByteVal=i;
}


Byte::Byte(NJString s)
{
  // TO BE DONE
  theByteVal=0;
}


NJString Byte::toString()
{
  // TO BE DONE
  return NULL;
}

