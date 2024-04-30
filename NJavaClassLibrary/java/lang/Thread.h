#ifndef NICKVM_JAVAC_THREAD_H
#define NICKVM_JAVAC_THREAD_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Applet;


const int MIN_PRIORITY=1;


class Thread : public __njobjectInternal {
public:
  Thread();
  //
  void setPriority(unsigned int p);
  void start();
  //
protected:
  bool running;
  unsigned int priority;
  Applet *_nickvmApplet;  // NOTE: May be NULL!
};


// Thread global funcs
Thread *Thread_currentThread();


#endif // NICKVM_JAVAC_THREAD_H

