
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


#include "__njobjectInternal.h"


////////////////////////////////////////////////////////////////////////////////
//  __njobjectInternal Class
////////////////////////////////////////////////////////////////////////////////


__njobjectInternal::__njobjectInternal()
{
}



