
//#define DEBUG_OUT dBug
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
#define CONS_OUT std::cout
//#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


// FIXME: Problem with circular reference between njavacpp.h Stream.h and _nickvm_System.h
class __njstreamInternal;


#include "__njsystemInternal.h"


// Kludge extern global object (not all static funcs)
__njsystemInternal *_nickvm___njsystemInternalGlobal=NULL;
//extern __njsystemInternal *System;


///////////////////////////////////////////////////////////////////////////////
//  __njsystemInternal global funcs
///////////////////////////////////////////////////////////////////////////////

void _nickvm___njsystemInternal_arraycopy(float *src, int srcPos, float *dest, int destPos, int length)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvm___njsystemInternal_arraycopy(,"<<srcPos<<",,"<<destPos<<","<<length<<")\n";
#endif // DEBUG_VERBOSE
  for(int t=0;t<length;t++) {
    dest[destPos+t]=src[srcPos+t];
  }
}


void _nickvm___njsystemInternal_arraycopy(int *src, int srcPos, int *dest, int destPos, int length)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvm___njsystemInternal_arraycopy(,"<<srcPos<<",,"<<destPos<<","<<length<<")\n";
#endif // DEBUG_VERBOSE
  for(int t=0;t<length;t++) {
    dest[destPos+t]=src[srcPos+t];
  }
}


///////////////////////////////////////////////////////////////////////////////
//  __njsystemInternal Class
///////////////////////////////////////////////////////////////////////////////

__njsystemInternal::__njsystemInternal()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"__njsystemInternal::__njsystemInternal()\n";
#endif // DEBUG_VERBOSE
  in=new __njstreamInternal();
  out=new __njstreamInternal();
  err=new __njstreamInternal();
}


char *__njsystemInternal::getProperty(char *s)
{
  ERR_OUT<<"__njsystemInternal::getProperty() not implemented!\n";
  exit(EXIT_FAILURE);
  return NULL;
}


void __njsystemInternal::exit(int ret)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"__njsystemInternal::exit()\n";
#endif // DEBUG_VERBOSE
  ::exit(ret);
}

