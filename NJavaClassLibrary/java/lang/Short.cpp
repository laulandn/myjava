
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


#include "Short.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  Short Class
////////////////////////////////////////////////////////////////////////////////

Short::Short(short i)
{
  theShort=i;
}


Short::Short(NJString s)
{
  // TO BE DONE
  theShort=0;
}


NJString Short::toString()
{
  // TO BE DONE
  return NULL;
}

