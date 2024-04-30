
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


#include "../../../cpp/alib/adebug.h"
#include "../../../../more_src/nlib/nlibdbug.h"

#include "NJavaInterface.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaInterface Class
////////////////////////////////////////////////////////////////////////////////


/*
NJavaInterface::NJavaInterface()
{
  debug_msg("NJavaInterface::NJavaInterface()\n");
  init();
}
*/


// NOTE: These params are the first two letters in the order they appear as data members
NJavaInterface::NJavaInterface()
{
  debug_msg("NJavaInterface::NJavaInterface()\n");
  init();
  addr=0;
  nameIndex=0;
}


NJavaInterface::~NJavaInterface()
{
}


void NJavaInterface::init()
{
  addr=0;
  nameIndex=0;
}


void NJavaInterface::debugDump()
{
  debug_msg("NJavaInterface: ");
  debug_msg(ALIB2HEX8(addr));
  debug_msg(",");
  debug_int(nameIndex);
  debug_msg("\n");
}
