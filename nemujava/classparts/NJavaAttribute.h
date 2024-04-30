#ifndef NJCLASSFILE_NJAVAATTRIBUTE_H
#define NJCLASSFILE_NJAVAATTRIBUTE_H


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BSymbol.h"

#include "../../NJavaClassLibrary/njtypes.h"


class NJavaAttribute : public BSymbol {
public:
  NJavaAttribute();
  virtual ~NJavaAttribute();
  //
  virtual void debugDump();
  //
  virtual ULONG getNameIndex() { return nameIndex; }
  virtual ULONG getData() { return data; }
  //
protected:
  //
  virtual void init();
  //
  UINT nameIndex;     // index into constants
  UINT data;     // virt addr of start of data
  //
};


#endif
