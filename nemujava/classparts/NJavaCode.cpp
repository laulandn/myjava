
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


#include "../../../cpp/alib/adebug.h"
#include "../../../../more_src/nlib/nlibdbug.h"

#include "NJavaCode.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaCode Class
////////////////////////////////////////////////////////////////////////////////


// NOTE: The param naming method used here are different than in the other classes!
NJavaCode::NJavaCode(UINT a,UINT n,UINT l,UINT sm,UINT lm,UINT cl,UINT ca,UINT el,UINT ea,UINT na,UINT aa)
{
  DEBUG_OUT<<"NJavaCode::NJavaCode(UINT "<<a<<",UINT "<<n<<",UINT "<<l<<",UINT "<<sm<<",UINT "<<lm<<",UINT "<<cl<<",UINT "<<ca<<",UINT "<<el<<",UINT "<<ALIB2HEX8(ea)<<",UINT "<<na<<",UINT "<<aa<<")\n";
  init();
  addr=a;
  nameIndex=n;
  theSize=l;
  stackMax=sm;
  localsMax=lm;
  codeLen=cl;
  codeAddr=ca;
  exceptionLen=el;
  exceptionAddr=ea;
  numAttrib=na;
  attribAddr=aa;
}


NJavaCode::~NJavaCode()
{
}


void NJavaCode::init()
{
  addr=0;
  nameIndex=0;
  theSize=0;
  stackMax=0;
  localsMax=0;
  codeLen=0;
  codeAddr=0;
  exceptionLen=0;
  exceptionAddr=0;
  numAttrib=0;
  attribAddr=0;
}


void NJavaCode::debugDump()
{
  DEBUG_OUT<<"NJavaCode: "<<ALIB2HEX8(addr)<<","<<nameIndex<<","<<theSize<<","<<stackMax<<","<<localsMax<<","<<codeLen<<","<<codeAddr<<","<<exceptionLen<<","<<exceptionAddr<<","<<numAttrib<<","<<attribAddr<<"\n";
}
