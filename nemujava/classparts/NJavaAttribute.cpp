

#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


#include "../../../cpp/alib/adebug.h"

#include "../../../../more_src/nlib/nlibdbug.h"

#include "NJavaAttribute.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaAttribute Class
////////////////////////////////////////////////////////////////////////////////


/*
NJavaAttribute::NJavaAttribute()
{
  CONS_OUT<<"NJavaAttribute::NJavaAttribute() WARNING! Deprecated! Please use params!\n";
  init();
}
*/


NJavaAttribute::NJavaAttribute()
{
  DEBUG_OUT<<"NJavaConstant::NJavaConstant()\n";
  addr=0;
  nameIndex=0;
  theSize=0;
  data=0;
  init();
}


NJavaAttribute::~NJavaAttribute()
{
}


void NJavaAttribute::init()
{
  addr=0;
  nameIndex=0;
  theSize=0;
  data=0;
}


void NJavaAttribute::debugDump()
{
  debug_msg("NJavaAttribute: ");
  debug_msg(ALIB2HEX8(addr));
  debug_msg(",");
  debug_int(nameIndex);
  debug_msg(",");
  debug_int(theSize);
  debug_msg(",");
  debug_int(data);
  debug_msg("\n");
}
