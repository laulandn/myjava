#ifndef NJCLASSFILE_NJAVAINTERFACE_H
#define NJCLASSFILE_NJAVAINTERFACE_H


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BSymbol.h"

#include "../../NJavaClassLibrary/njtypes.h"


class NJavaInterface : public BSymbol {
public:
  NJavaInterface();
  virtual ~NJavaInterface();
  //
  virtual void debugDump();
  //
  virtual ULONG getNameIndex() { return nameIndex; }
  //
protected:
  //
  virtual void init();
  //
  UINT nameIndex;     // index into constants
  //
};


#endif
