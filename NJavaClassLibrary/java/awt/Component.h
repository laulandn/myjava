#ifndef NICKVM_JAVAC_COMPONENT_H
#define NICKVM_JAVAC_COMPONENT_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"

#include "NJAWTBaseObject.h"


class Graphics;


class Component : public NJAWTBaseObject {
public:
  Component();
  //
  virtual void repaint();
  virtual void paint(Graphics *g);
  virtual void update();
  //
protected:
};


#endif
