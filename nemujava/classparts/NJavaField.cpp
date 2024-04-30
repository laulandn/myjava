
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


#include "../../../cpp/alib/adebug.h"
#include "../../../../more_src/nlib/nlibdbug.h"

#include "NJavaField.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaField Class
////////////////////////////////////////////////////////////////////////////////


// NOTE: These params are the first two letters in the order they appear as data members
NJavaField::NJavaField()
{
  debug_msg("NJavaField::NJavaField()\n");
  init();
  addr=0;
  nameIndex=0;
}


NJavaField::~NJavaField()
{
}


void NJavaField::init()
{
  addr=0;
  nameIndex=0;
}


void NJavaField::debugDump()
{
  debug_msg("NJavaField: ");
  debug_msg(ALIB2HEX8(addr));
  debug_msg(",");
  debug_int(nameIndex);
  debug_msg("\n");
}
