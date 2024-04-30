
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


#include "Exception.h"


////////////////////////////////////////////////////////////////////////////////
//  Exception Class
////////////////////////////////////////////////////////////////////////////////

Exception::Exception()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Exception::Exception()\n";
#endif // DEBUG_VERBOSE
  name=(NJString)"Unnamed exception";
}


Exception::Exception(NJString s)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Exception::Exception(\""<<s<<"\")\n";
#endif // DEBUG_VERBOSE
  name=s;
}


NJString Exception::toString()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Exception::toString()\n";
#endif // DEBUG_VERBOSE
  return (NJString)"Exception_toString";
}


