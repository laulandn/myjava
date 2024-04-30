#ifndef NICKVM_JAVAC_STREAM_H
#define NICKVM_JAVAC_STREAM_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


#include "../NJString.h"


class Stream : public __njobjectInternal {
public:
  Stream(NJString fn);
  //
  NJString getName();
  //
protected:
  NJString name;
};


#endif

