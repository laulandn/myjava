#ifndef NICKVM_JAVAC_DOUBLE_H
#define NICKVM_JAVAC_DOUBLE_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


#include "../NJString.h"


class Double : public __njobjectInternal {
public:
  Double(double t);
  Double(NJString s);
  //
  NJString toString();
  double DoubleValue();
  //
protected:
  double theDoubleVal;
};


// Double global funcs

Double *Double_valueOf(NJString s);

void System_arraycopy(double *src, int srcPos, double *dest, int destPos, int length);


#endif

