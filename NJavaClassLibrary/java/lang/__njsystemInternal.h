#ifndef NICKVM_JAVAC_NICKVM_NJSYSTEMINTERNAL_H
#define NICKVM_JAVAC_NICKVM_NJSYSTEMINTERNAL_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../util/__njstreamInternal.h"


class __njstreamInternal;


// global funcs
void _nickvm___njsystemInternal_arraycopy(float *src, int srcPos, float *dest, int destPos, int length);
void _nickvm___njsystemInternal_arraycopy(int *src, int srcPos, int *dest, int destPos, int length);


class __njsystemInternal : public __njobjectInternal {
public:
  __njsystemInternal();
  //
  char *getProperty(char *s);
  void exit(int ret);
  //
  __njstreamInternal *in;
  __njstreamInternal *out;
  __njstreamInternal *err;
  //
protected:
};


// Kludge extern global object (not all static funcs)
extern __njsystemInternal *_nickvm___njsystemInternalGlobal;
//extern __njsystemInternal *System;


#endif

