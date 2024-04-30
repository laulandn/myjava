#ifndef NICKVM_JAVAC_EVENT_H
#define NICKVM_JAVAC_EVENT_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Event : public __njobjectInternal {
public:
  int x,y;
  int val;
  int type;
};


#endif

