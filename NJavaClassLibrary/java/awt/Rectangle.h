#ifndef NICKVM_JAVAC_RECTANGLE_H
#define NICKVM_JAVAC_RECTANGLE_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Rectangle : public __njobjectInternal {
public:
  Rectangle(int,int);
  //
  int x,y;
  int width,height;
};


#endif

