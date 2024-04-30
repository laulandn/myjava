#ifndef NJCLASSFILE_NJAVAMETHOD_H
#define NJCLASSFILE_NJAVAMETHOD_H


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BSymbol.h"

#include "../../NJavaClassLibrary/njtypes.h"


// Stupid temp fix
#ifndef EADDR_T
#define EADDR_T ULONG
#endif


class NJavaCode;


class NJavaMethod : public BSymbol {
public:
  // NOTE: These params are the first two letters in the order they appear as data members (see below)
  NJavaMethod();
  virtual ~NJavaMethod();
  //
  virtual void debugDump();
  //
  virtual NJavaCode *getTheCode() { return theCode; }
  virtual void setTheCode(NJavaCode *newCode);
  //
//protected:
  //
  virtual void init();
  //
  UINT nameIndex;     // index into constants
  UINT flags;
  UINT desc;     // index into constants
  UINT numAttributes;      // number of attributes attached
  UINT attributes; // virt addr of first attribute
  NJavaCode *theCode;  // If NULL not defined
  //
};


#endif
