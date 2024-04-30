#ifndef NICKVM_JAVAC_INTEGER_H
#define NICKVM_JAVAC_INTEGER_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Integer : public __njobjectInternal {
public:
  Integer(int i);
  //Integer(String *s);
  Integer(NJString );
  //
  NJString toString();
  int intValue();
  //
protected:
  int theIntegerVal;
};


#endif

