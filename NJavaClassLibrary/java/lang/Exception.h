#ifndef NICKVM_JAVAC_EXCEPTION_H
#define NICKVM_JAVAC_EXCEPTION_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Exception : public __njobjectInternal {
public:
  Exception();
  Exception(NJString s);
  //
  NJString toString();
  //
protected:
  NJString name;
};


#endif

