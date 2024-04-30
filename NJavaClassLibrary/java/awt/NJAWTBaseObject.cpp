
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


#include "NJAWTBaseObject.h"


////////////////////////////////////////////////////////////////////////////////
//  NJAWTBaseObject Class
////////////////////////////////////////////////////////////////////////////////

NJAWTBaseObject::NJAWTBaseObject()
{
  init();
}


NJAWTBaseObject::NJAWTBaseObject(char *s)
{
  init();
  text=s;
}


void NJAWTBaseObject::init()
{
  text=NULL;
  fc=NULL;
  bc=NULL;
}
