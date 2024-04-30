
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#include "Applet.h"

#include "../awt/Graphics.h"
#include "../awt/Rectangle.h"


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "../../../../cpp/alib/apalette.h"

#include "../../../../cpp/guilib/AWindow.h"
#include "../../../../cpp/guilib/AEvent.h"
#include "../../../../cpp/guilib/AApplicationLoop.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


void _nickvmAppletMousedownProxy(AEvent *e);
void _nickvmAppletMouseupProxy(AEvent *e);
void _nickvmAppletMousemoveProxy(AEvent *e);
void _nickvmAppletMousedragProxy(AEvent *e);
void _nickvmAppletRedrawProxy(AEvent *e);
void _nickvmAppletDestroyProxy(AEvent *e);
void _nickvmAppletKeydownProxy(AEvent *e);
void _nickvmAppletKeymoveProxy(AEvent *e);


// Only one for now, global so everyone can get to it
Applet *_nickvmDefApplet=NULL;


////////////////////////////////////////////////////////////////////////////////
//  Applet Class
////////////////////////////////////////////////////////////////////////////////

Applet::Applet()
{
  _nickvmWin=new AWindow("myjava Applet",640,480);
  if(_nickvmWin) {
    if(!_nickvmWin->err.getError()) {
      box.width=_nickvmWin->getWidth();
      box.height=_nickvmWin->getHeight();
    }
    else err.setError();
  }
  else err.setError();
  if(err.getError()) {
    ERR_OUT<<"Applet::Applet something wrong with the window I requested!\n";
    exit(EXIT_FAILURE);
  }
  gfx=new Graphics();
  gfx->_nickvmSetWindow(_nickvmWin);
  base=(NJString)".";
  curParam=1;
  _nickvmDefApplet=this;
  needsPaint=true;
  buttonPressed=false;
  defaultThread=new Thread();
  _nickvmLoop=new AApplicationLoop(_nickvmWin);
}


Applet::~Applet()
{
  if(_nickvmWin) delete _nickvmWin;
  _nickvmWin=NULL;
}


NJString Applet::getParameter(NJString p)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::getParameter(\""<<p<<"\")\n";
#endif // DEBUG_VERBOSE
  NJString ret=NULL;
  //ret=aThisApp.argv[curParam];
  curParam++;
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"going to return \""<<ret<<"\"\n";
#endif // DEBUG_VERBOSE
  return ret;
}


NJString Applet::getDocumentBase()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::getDocumentBase()\n";
#endif // DEBUG_VERBOSE
  return base;
}


void Applet::notifyAll()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::notifyAll()\n";
#endif // DEBUG_VERBOSE
}


void Applet::resize(unsigned int nw, unsigned int nh)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::resize("<<nw<<","<<nh<<")\n";
#endif // DEBUG_VERBOSE
  if(_nickvmWin) if(!_nickvmWin->err.getError()) _nickvmWin->resizeWindow(nw,nh);
}


__njrectInternal *Applet::getSize()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::size()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmWin) {
    if(!_nickvmWin->err.getError()) {
      _nickvmWin->updateWindowFields();
      box.width=_nickvmWin->getWidth();
      box.height=_nickvmWin->getHeight();
    }
  }
  return &box;
}


void Applet::run()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::run()\n";
#endif // DEBUG_VERBOSE
}


void Applet::start()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::start()\n";
#endif // DEBUG_VERBOSE
  if(defaultThread) defaultThread->start();
}


void Applet::stop()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::stop()\n";
#endif // DEBUG_VERBOSE
}


void Applet::wait()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::wait()\n";
#endif // DEBUG_VERBOSE
}


jboolean Applet::mouseDown(Event *e,int x,int y)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::mouseDown()\n";
#endif // DEBUG_VERBOSE
  return true;
}


jboolean Applet::mouseUp(Event *e,int x,int y)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::mouseUp()\n";
#endif // DEBUG_VERBOSE
  return true;
}


jboolean Applet::mouseMove(Event *e,int x,int y)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::mouseMove()\n";
#endif // DEBUG_VERBOSE
  return true;
}


jboolean Applet::mouseDrag(Event *e,int x,int y)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::mouseDrag()\n";
#endif // DEBUG_VERBOSE
  return true;
}


void Applet::repaint()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::repaint()\n";
#endif // DEBUG_VERBOSE
  needsPaint=true;
  paint(gfx);
}


void Applet::paint(Graphics *g)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::paint()\n";
#endif // DEBUG_VERBOSE
  needsPaint=false;
}


void Applet::update()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::update()\n";
#endif // DEBUG_VERBOSE
  needsPaint=false;
}


void Applet::_nickvmTranslateEvent(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Applet::_nickvmTranslateEvent()\n";
#endif // DEBUG_VERBOSE
  if(!e) return;
  event.x=e->x;
  event.y=e->y;
  event.type=e->type;
  event.val=e->code;
}


void _nickvmAppletMousedownProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletMousedownProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
    _nickvmDefApplet->mouseDown(_nickvmDefApplet->_nickvmGetEvent(),e->x,e->y);
    _nickvmDefApplet->buttonPressed=true;
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletMouseupProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletMouseupProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
    _nickvmDefApplet->mouseUp(_nickvmDefApplet->_nickvmGetEvent(),e->x,e->y);
    _nickvmDefApplet->buttonPressed=false;
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletMousemoveProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletMousemoveProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
    _nickvmDefApplet->mouseMove(_nickvmDefApplet->_nickvmGetEvent(),e->x,e->y);
    if(_nickvmDefApplet->buttonPressed) _nickvmAppletMousedragProxy(e);
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletRedrawProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletRedrawProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
    _nickvmDefApplet->repaint();
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletMousedragProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletMousedragProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
    _nickvmDefApplet->mouseDrag(_nickvmDefApplet->_nickvmGetEvent(),e->x,e->y);
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletDestroyProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletDestroyProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
    exit(EXIT_SUCCESS);
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletKeydownProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletKeydownProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
  }
  else ERR_OUT<<"no applet!\n";
}


void _nickvmAppletKeyupProxy(AEvent *e)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"_nickvmAppletKeyupProxy()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmDefApplet) {
    _nickvmDefApplet->_nickvmTranslateEvent(e);
  }
  else ERR_OUT<<"no applet!\n";
}


