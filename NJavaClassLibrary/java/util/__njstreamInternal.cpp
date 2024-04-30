
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
#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


// FIXME: Problem with circular reference between njavacpp.h Stream.h and System.h
class __njstreamInternal;


#include "__njstreamInternal.h"


////////////////////////////////////////////////////////////////////////////////
//  __njstreamInternal Class
////////////////////////////////////////////////////////////////////////////////

__njstreamInternal::__njstreamInternal()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"__njstreamInternal::__njstreamInternal()\n";
#endif // DEBUG_VERBOSE
}


void __njstreamInternal::println()
{
  CONS_OUT<<"\n";
}


void __njstreamInternal::print(int i)
{
  CONS_OUT<<i;
}


void __njstreamInternal::println(int i)
{
  print(i);
  CONS_OUT<<"\n";
}


void __njstreamInternal::print(const char *s)
{
  CONS_OUT<<s;
}


void __njstreamInternal::println(const char *s)
{
  print(s);
  CONS_OUT<<"\n";
}


