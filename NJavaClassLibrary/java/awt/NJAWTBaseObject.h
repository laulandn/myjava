#ifndef NICKVM_JAVACNJAWTBaseObject_H
#define NICKVM_JAVACNJAWTBaseObject_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


class Color;


#include "../../njavacpp.h"


class NJAWTBaseObject : public __njobjectInternal {
public:
  NJAWTBaseObject();
  NJAWTBaseObject(char *s);
  //
  void addItem(char *s);
  void setForeground(Color *c);
  void setBackground(Color *c);
  //
protected:
  //
  void init();
  //
  char *text;
  Color *fc;
  Color *bc;
};


#endif
