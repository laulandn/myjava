#ifndef NICKVM_JAVAC_SHORT_H
#define NICKVM_JAVAC_SHORT_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Short : public __njobjectInternal {
public:
  Short(short i);
  Short(NJString s);
  //
  NJString toString();
  short shortValue();
  //
protected:
  short theShort;
};


#endif

