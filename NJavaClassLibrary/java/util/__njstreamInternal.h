#ifndef NICKVM_JAVAC_NJSTREAMINTERNAL_H
#define NICKVM_JAVAC_NJSTREAMINTERNAL_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


#include "../NJString.h"


class __njstreamInternal : public __njobjectInternal {
public:
  __njstreamInternal();
  //
  void println();
  void print(int i);
  void println(int i);
  void print(const char *s);
  void println(const char *s);
  //
protected:
};


#endif

