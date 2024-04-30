
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


#include "__njstringInternal.h"


#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////
//  __njstringInternal globals
////////////////////////////////////////////////////////////////////////////////

// global "NULL" string object
__njstringInternal __njstringInternal_NULL(NULL);


////////////////////////////////////////////////////////////////////////////////
//  __njstringInternal Class
////////////////////////////////////////////////////////////////////////////////


__njstringInternal::__njstringInternal()
{
  theStringVal=NULL;
}


__njstringInternal::__njstringInternal(char *s)
{
  theStringVal=s;
}

