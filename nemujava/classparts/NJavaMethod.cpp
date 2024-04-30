
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


#include "../../../cpp/alib/adebug.h"
#include "../../../../more_src/nlib/nlibdbug.h"

#include "NJavaMethod.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaMethod Class
////////////////////////////////////////////////////////////////////////////////


// NOTE: These params are the first two letters in the order they appear as data members
NJavaMethod::NJavaMethod()
{
  debug_msg("NJavaMethod::NJavaMethod()\n");
  init();
  addr=0;
  nameIndex=0;
  flags=0;
  desc=0;
  numAttributes=0;
  attributes=0;
}


NJavaMethod::~NJavaMethod()
{
}


void NJavaMethod::init()
{
  addr=0;
  nameIndex=0;
  flags=0;
  desc=0;
  numAttributes=0;
  attributes=0;
  theCode=NULL;
}


void NJavaMethod::setTheCode(NJavaCode *newCode)
{
  theCode=newCode;
}


void NJavaMethod::debugDump()
{
  debug_msg("NJavaMethod: ");
  debug_msg((ALIB2HEX8(addr)));
  debug_msg(",");
  debug_int(nameIndex);
  debug_msg(",");
  debug_int(flags);
  debug_msg(",");
  debug_int(desc);
  debug_msg(",");
  debug_int(numAttributes);
  debug_msg(",");
  debug_int(attributes);
  debug_msg("\n");
}
