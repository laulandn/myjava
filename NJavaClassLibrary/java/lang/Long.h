#ifndef NICKVM_JAVAC_LONG_H
#define NICKVM_JAVAC_LONG_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Long : public __njobjectInternal {
public:
  Long(long i);
  Long(NJString s);
  //
  NJString toString();
  long longValue();
  //
protected:
  long theLongVal;
};


#endif

