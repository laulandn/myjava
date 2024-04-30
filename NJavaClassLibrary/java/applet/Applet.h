#ifndef NICKVM_JAVAC_Applet_H
#define NICKVM_JAVAC_Applet_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"

#include "../__njrectInternal.h"

#include "../lang/Thread.h"

#include "../awt/Component.h"
#include "../awt/Event.h"


// Internal...
class AWindow;
class AEvent;
class AApplicationLoop;
class AColor;


class Thread;
class Graphics;
class Float;
class Color;


class Applet : public Component {
public:
  Applet();
  virtual ~Applet();
  //
  NJString getParameter(NJString p);
  NJString getDocumentBase();
  __njrectInternal *getSize();
  // The next method is deprecated!
  __njrectInternal *size() { return getSize(); }
  __njrectInternal *bounds() { return getSize(); } // not sure...
  void setBackground(Color *c);
  Color *getBackground();
  Graphics *getGraphics() { return gfx; }
  //
  virtual void repaint();
  virtual void paint(Graphics *g);
  virtual void update();
  //
  void notifyAll();
  virtual void wait();
  //
  virtual void run();
  virtual void start();
  virtual void stop();
  //
  virtual void resize(unsigned int w, unsigned int h);
  virtual jboolean mouseUp(Event *e,int x,int y);
  virtual jboolean mouseDown(Event *e,int x,int y);
  virtual jboolean mouseMove(Event *e,int x,int y);
  virtual jboolean mouseDrag(Event *e,int x,int y);
  //
  AApplicationLoop *_nickvmGetLoop() { return _nickvmLoop; }
  Event *_nickvmGetEvent() { return &event; }
  void _nickvmTranslateEvent(AEvent *e);
  //
  bool buttonPressed;
  //
protected:
  __njrectInternal box;
  Graphics *gfx;
  Event event;
  NJString base;
  Thread *defaultThread;
  unsigned int curParam;
  bool needsPaint;
  // Internal...
  AWindow *_nickvmWin;
  AApplicationLoop *_nickvmLoop;
};


#endif // NICKVM_JAVAC_Applet_H

