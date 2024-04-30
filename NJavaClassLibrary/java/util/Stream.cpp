
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


// FIXME: Problem with circular reference between njavacpp.h Stream.h and System.h
class NJInternalStream;


#include "Stream.h"


////////////////////////////////////////////////////////////////////////////////
//  Stream Class
////////////////////////////////////////////////////////////////////////////////

Stream::Stream(NJString fn)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Stream::Stream(\""<<fn<<"\")\n";
#endif // DEBUG_VERBOSE
  name=fn;
}


NJString Stream::getName()
{
  return name;
}


