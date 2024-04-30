
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#include "Color.h"
#include "Rectangle.h"
#include "Graphics.h"


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "../../../../cpp/alib/apalette.h"

#include "../../../../cpp/guilib/AWindow.h"
#include "../../../../cpp/guilib/AEvent.h"
#include "../../../../cpp/guilib/AApplicationLoop.h"


void _nickvmAppletMousedownProxy(AEvent *e);
void _nickvmAppletMouseupProxy(AEvent *e);
void _nickvmAppletMousemoveProxy(AEvent *e);
void _nickvmAppletMousedragProxy(AEvent *e);
void _nickvmAppletRedrawProxy(AEvent *e);
void _nickvmAppletDestroyProxy(AEvent *e);
void _nickvmAppletKeydownProxy(AEvent *e);
void _nickvmAppletKeymoveProxy(AEvent *e);


////////////////////////////////////////////////////////////////////////////////
//  Graphics Class
////////////////////////////////////////////////////////////////////////////////

Graphics::Graphics()
{
  _nickvmWindow=NULL;
  r=NULL;
  fm=NULL;
}


void Graphics::drawString(NJString text,unsigned int x, unsigned int y)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Graphics::drawString()\n";
#endif // DEBUG_VERBOSE
}


void Graphics::setColor(Color c)
{
  setColor(&c);
}


void Graphics::setColor(Color *c)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Graphics::setColor()\n";
#endif // DEBUG_VERBOSE
  if(_nickvmWindow) {
    if(c->_nickvmColor) {
      unsigned int r=c->_nickvmColor->red,g=c->_nickvmColor->green,b=c->_nickvmColor->blue;
      //
      // Force everything pink for testing...
      //r=0xff; g=0x80; b=0x80;
      //
      unsigned long rgb=(r<<16)|(b<<8)|g;
#ifdef DEBUG_VERBOSE
      DEBUG_OUT<<"rgb is "<<rgb<<"\n";
#endif // DEBUG_VERBOSE
      _nickvmWindow->setForeground(rgb,true);
    }
    else { ERR_OUT<<"No color c!\n"; exit(EXIT_SUCCESS); }
  }
  else { ERR_OUT<<"No window w!\n"; exit(EXIT_SUCCESS); }
}


void Graphics::drawLine(int a,int b,int c,int d)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Graphics::drawLine("<<a<<","<<b<<","<<c<<","<<d<<")\n";
#endif // DEBUG_VERBOSE
  if(_nickvmWindow) {
    _nickvmWindow->drawLine(a,b,c,d);
  }
  else ERR_OUT<<"no window!\n";
}


void Graphics::fillRect(int a,int b,int c,int d)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Graphics::fillRect("<<a<<","<<b<<","<<c<<","<<d<<")\n";
#endif // DEBUG_VERBOSE
  if(_nickvmWindow) {
    _nickvmWindow->moveTo(a,b);
    _nickvmWindow->drawFilledRect(a+c,b+d);
  }
  else ERR_OUT<<"no window!\n";
}


// NOTE!  Just a rectangle NOT an oval for now!
void Graphics::fillOval(int a,int b,int c,int d)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Graphics::fillOval("<<a<<","<<b<<","<<c<<","<<d<<")\n";
#endif // DEBUG_VERBOSE
  if(_nickvmWindow) {
    _nickvmWindow->moveTo(a,b);
    _nickvmWindow->drawFilledRect(a+c,b+d);
  }
  else ERR_OUT<<"no window!\n";
}


void Graphics::_nickvmSetWindow(AWindow *win)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Graphics::nickvmSetWindow()\n";
#endif // DEBUG_VERBOSE
  _nickvmWindow=win;
}


void Graphics::_nickvmEraseWindow()
{
  if(_nickvmWindow) _nickvmWindow->clearWindow();
}


