#ifndef NJCLASSFILE_NJAVAFIELD_H
#define NJCLASSFILE_NJAVAFIELD_H


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BSymbol.h"

#include "../../NJavaClassLibrary/njtypes.h"


class NJavaField : public BSymbol {
public:
  NJavaField();
  virtual ~NJavaField();
  //
  virtual void debugDump();
  //
//protected:
  //
  virtual void init();
  //
  UINT nameIndex;     // index into constants
  //
};


#endif
