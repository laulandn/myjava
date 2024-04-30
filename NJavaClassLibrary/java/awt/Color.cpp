
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


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "../../../../cpp/alib/apalette.h"


////////////////////////////////////////////////////////////////////////////////
//  Color Class
////////////////////////////////////////////////////////////////////////////////


Color::Color()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Color::Color()\n";
#endif // DEBUG_VERBOSE
  _nickvmColor=new AColor;
  _nickvmColor->red=0;
  _nickvmColor->green=0;
  _nickvmColor->blue=0;
}


Color::Color(int r,int g,int b)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Color::Color("<<r<<","<<g<<","<<b<<")\n";
#endif // DEBUG_VERBOSE
  _nickvmColor=new AColor;
  _nickvmColor->red=r;
  _nickvmColor->green=g;
  _nickvmColor->blue=b;
}



