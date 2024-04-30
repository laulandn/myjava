
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "Float.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  Float global funcs
////////////////////////////////////////////////////////////////////////////////


Float* Float_valueOf(NJString s)
{
  NJString t=s;
#ifdef NICK_STRINGS_ARE_OBJECTS
  if(!t._nickvm_String_is_null()) t=_nickvm_String_Null;
#else
  if(!t) t=NULL;
#endif
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Float_valueOf(\""<<t<<"\")\n";
#endif // DEBUG_VERBOSE
  float f=0.0;
#ifdef NICK_STRINGS_ARE_OBJECTS
  if(!t._nickvm_String_is_null()) sscanf(t._nickvm_String_charptr(),"%f",&f);
#else
  if(t) sscanf(t,"%f",&f);
#endif
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"going to return "<<f<<"\n";
#endif // DEBUG_VERBOSE
  return new Float(f);
}


////////////////////////////////////////////////////////////////////////////////
//  Float Class
////////////////////////////////////////////////////////////////////////////////

Float::Float(float t)
{
  theFloatVal=t;
}


float Float::floatValue()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Float::floatValue()\n";
  DEBUG_OUT<<"going to return "<<theFloatVal<<"\n";
#endif // DEBUG_VERBOSE
  return theFloatVal;
}


