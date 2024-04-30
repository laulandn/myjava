#ifndef NICKVM_JAVAC_FLOAT_H
#define NICKVM_JAVAC_FLOAT_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Float : public __njobjectInternal {
public:
  Float(float t);
  Float(NJString s);
  //
  NJString toString();
  float floatValue();
  //
protected:
  float theFloatVal;
};


// Float global funcs

Float *Float_valueOf(NJString s);

void System_arraycopy(float *src, int srcPos, float *dest, int destPos, int length);


#endif

