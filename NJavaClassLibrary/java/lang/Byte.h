#ifndef NICKVM_JAVAC_BYTE_H
#define NICKVM_JAVAC_BYTE_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Byte : public __njobjectInternal {
public:
  Byte(jbyte i);
  Byte(NJString s);
  //
  NJString toString();
  jbyte jbyteValue();
  //
protected:
  jbyte theByteVal;
};


#endif

