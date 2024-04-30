#ifndef NICKVM_JAVAC_Graphics_H
#define NICKVM_JAVAC_Graphics_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


// Internal...
class AWindow;


class Color;
class FontMetrics;
class Rectangle;


class Graphics : public __njobjectInternal {
public:
  Graphics();
  //
  // Due to problems with pointers in the compiler...
  virtual void setColor(Color *c);
  virtual void setColor(Color c);
  virtual FontMetrics *getFontMetrics() { return fm; }
  virtual Rectangle *getClipBounds() { return r; }
  //
  virtual void drawString(NJString text,unsigned int x, unsigned int y);
  virtual void drawLine(int,int,int,int);
  virtual void fillRect(int,int,int,int);
  virtual void fillOval(int,int,int,int);
  //
  // Internal...
  virtual void _nickvmSetWindow(AWindow *win);
  virtual void _nickvmEraseWindow();
  //
protected:
  //
  FontMetrics *fm;
  Rectangle *r;
  //
  // Internal...
  AWindow *_nickvmWindow;
  //
};


#endif // NICKVM_JAVAC_Graphics_H

