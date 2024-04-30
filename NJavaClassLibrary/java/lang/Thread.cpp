
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#include "Thread.h"

#include "../applet/Applet.h"


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "../../../../cpp/guilib/AWindow.h"
#include "../../../../cpp/guilib/AEvent.h"
#include "../../../../cpp/guilib/AApplicationLoop.h"


extern Applet *_nickvmDefApplet;


void _nickvmAppletMousedownProxy(AEvent *e);
void _nickvmAppletMouseupProxy(AEvent *e);
void _nickvmAppletMousemoveProxy(AEvent *e);
void _nickvmAppletMousedragProxy(AEvent *e);
void _nickvmAppletRedrawProxy(AEvent *e);
void _nickvmAppletDestroyProxy(AEvent *e);
void _nickvmAppletKeyupProxy(AEvent *e);
void _nickvmAppletKeydownProxy(AEvent *e);
void _nickvmAppletKeymoveProxy(AEvent *e);


// Default thread, global so everyone can get to it
Thread *_nickvmDefThread=NULL;


////////////////////////////////////////////////////////////////////////////////
//  Thread global funcs
////////////////////////////////////////////////////////////////////////////////

Thread *Thread_currentThread()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Thread_currentThread()\n";
#endif // DEBUG_VERBOSE
  return new Thread();
}


////////////////////////////////////////////////////////////////////////////////
//  Thread Class
////////////////////////////////////////////////////////////////////////////////

Thread::Thread()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Thread::Thread()\n";
#endif // DEBUG_VERBOSE
  _nickvmApplet=_nickvmDefApplet;
  if(!_nickvmApplet) ERR_OUT<<"NOTE: _nickvmApplet is NULL\n";
  running=false;
  priority=0;
  _nickvmDefThread=this;
}


void Thread::setPriority(unsigned int p)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Thread::setPriority("<<p<<")\n";
#endif // DEBUG_VERBOSE
  priority=p;
}


void Thread::start()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Thread::start()\n";
#endif // DEBUG_VERBOSE
  running=true;
  if(!_nickvmApplet) { ERR_OUT<<"Can't run, no Applet!\n"; err.setError(); return; }
  AApplicationLoop *loop=_nickvmApplet->_nickvmGetLoop();
  if(!loop) { ERR_OUT<<"Can't run, no ApplicationLoop!\n"; err.setError(); return; }
  loop->regEvent(A_EVENT_REDRAW,_nickvmAppletRedrawProxy);
  loop->regEvent(A_EVENT_RESIZE,_nickvmAppletRedrawProxy);
  loop->regEvent(A_EVENT_DESTROY,_nickvmAppletDestroyProxy);
  loop->regEvent(A_EVENT_BREAK,_nickvmAppletDestroyProxy);
  loop->regEvent(A_EVENT_MOUSEDOWN,_nickvmAppletMousedownProxy);
  loop->regEvent(A_EVENT_MOUSEUP,_nickvmAppletMouseupProxy);
  loop->regEvent(A_EVENT_MOUSEMOVE,_nickvmAppletMousemoveProxy);
  loop->regEvent(A_EVENT_KEYDOWN,_nickvmAppletKeydownProxy);
  loop->regEvent(A_EVENT_KEYUP,_nickvmAppletKeyupProxy);
  loop->run();
}


