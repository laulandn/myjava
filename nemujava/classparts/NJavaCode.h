#ifndef NJCLASSFILE_NJAVACODE_H
#define NJCLASSFILE_NJAVACODE_H


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BSymbol.h"

#include "../../NJavaClassLibrary/njtypes.h"


class NJavaCode : public BSymbol {
public:
  // NOTE: The param naming method used here are different than in the other classes!
  NJavaCode(UINT a,UINT n,UINT l,UINT sm,UINT lm,UINT cl,UINT ca,UINT el,UINT ea,UINT na,UINT aa);
  virtual ~NJavaCode();
  //
  virtual void debugDump();
  //
//protected:
  //
  virtual void init();
  //
  UINT nameIndex;
  UINT stackMax;
  UINT localsMax;
  UINT codeLen;
  UINT codeAddr;
  UINT exceptionLen;
  UINT exceptionAddr;
  UINT numAttrib;
  UINT attribAddr;
  //
};


#endif
