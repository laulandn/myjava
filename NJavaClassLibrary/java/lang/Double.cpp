
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


#include "Double.h"


#define _USE_MATH_DEFINES 1
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  Double global funcs
////////////////////////////////////////////////////////////////////////////////


Double *Double_valueOf(NJString s)
{
  NJString t=s;
#ifdef NICK_STRINGS_ARE_OBJECTS
  if(!t._nickvm_String_is_null()) t=_nickvm_String_Null;
#else
  if(!t) t=NULL;
#endif
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Double_valueOf(\""<<t<<"\")\n";
#endif // DEBUG_VERBOSE
  double f=0.0;
#ifdef NICK_STRINGS_ARE_OBJECTS
  if(!t._nickvm_String_is_null()) sscanf(t._nickvm_String_charptr(),"%lf",&f);
#else
  if(t) sscanf(t,"%lf",&f);
#endif
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"going to return "<<f<<"\n";
#endif // DEBUG_VERBOSE
  return new Double(f);
}


////////////////////////////////////////////////////////////////////////////////
//  Double Class
////////////////////////////////////////////////////////////////////////////////

Double::Double(double t)
{
  theDoubleVal=t;
}


double Double::DoubleValue()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Double::DoubleValue()\n";
  DEBUG_OUT<<"going to return "<<theDoubleVal<<"\n";
#endif // DEBUG_VERBOSE
  return theDoubleVal;
}


