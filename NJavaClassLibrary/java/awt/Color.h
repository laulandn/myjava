#ifndef NICKVM_JAVAC_COLOR_H
#define NICKVM_JAVAC_COLOR_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class AColor;


class Color : public __njobjectInternal {
public:
  Color();
  Color(int,int,int);
  //
  AColor *_nickvmColor;
  //
protected:
};


#endif

