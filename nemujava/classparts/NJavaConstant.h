#ifndef NJCLASSFILE_NJAVACONSTANT_H
#define NJCLASSFILE_NJAVACONSTANT_H


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BSymbol.h"

#include "../../NJavaClassLibrary/njtypes.h"


// Are these arbitrary or do they match the real thing?
#define ESYM_JAVA_OFFSET 0x400
#define ESYM_JAVA_CONSTANT    0+ESYM_JAVA_OFFSET
#define ESYM_JAVA_INTERFACE   1+ESYM_JAVA_OFFSET
#define ESYM_JAVA_FIELD       2+ESYM_JAVA_OFFSET
#define ESYM_JAVA_METHOD      3+ESYM_JAVA_OFFSET
#define ESYM_JAVA_METHOD_ATTR 4+ESYM_JAVA_OFFSET
#define ESYM_JAVA_METHOD_HAND 5+ESYM_JAVA_OFFSET
#define ESYM_JAVA_ATTR        6+ESYM_JAVA_OFFSET
#define ESYM_JAVA_CODE        7+ESYM_JAVA_OFFSET
#define ESYM_JAVA_UTF8        8+ESYM_JAVA_OFFSET
#define ESYM_JAVA_FLOAT       9+ESYM_JAVA_OFFSET
#define ESYM_JAVA_LONG        10+ESYM_JAVA_OFFSET
#define ESYM_JAVA_DOUBLE      11+ESYM_JAVA_OFFSET
#define ESYM_JAVA_ARRAY       12+ESYM_JAVA_OFFSET
#define ESYM_JAVA_CLASS       13+ESYM_JAVA_OFFSET
#define ESYM_JAVA_STRING      14+ESYM_JAVA_OFFSET
#define ESYM_JAVA_NAMETYPE    15+ESYM_JAVA_OFFSET


// Are these arbitrary or do they match the real thing?
#define ESYM_JVM_OFFSET 0x500
#define ESYM_JVM_UTF8          1+ESYM_JVM_OFFSET
#define ESYM_JVM_INT           3+ESYM_JVM_OFFSET
#define ESYM_JVM_FLOAT         4+ESYM_JVM_OFFSET
#define ESYM_JVM_LONG          5+ESYM_JVM_OFFSET
#define ESYM_JVM_DOUBLE        6+ESYM_JVM_OFFSET
#define ESYM_JVM_CLASS         7+ESYM_JVM_OFFSET
#define ESYM_JVM_STRING        8+ESYM_JVM_OFFSET
#define ESYM_JVM_FIELD         9+ESYM_JVM_OFFSET
#define ESYM_JVM_METHOD        10+ESYM_JVM_OFFSET
#define ESYM_JVM_INTERFACE     11+ESYM_JVM_OFFSET
#define ESYM_JVM_NAMETYPE      12+ESYM_JVM_OFFSET
#define ESYM_JVM_METHODHAND    15+ESYM_JVM_OFFSET
#define ESYM_JVM_METHODTYPE    16+ESYM_JVM_OFFSET
#define ESYM_JVM_INVOKEDYNAMIC 18+ESYM_JVM_OFFSET


// I think I made these up...
#define ESYM_JVM_ARRAY         128+ESYM_JVM_OFFSET
#define ESYM_JVM_CODE          129+ESYM_JVM_OFFSET
#define ESYM_JVM_ATTR          130+ESYM_JVM_OFFSET
#define ESYM_JVM_METHOD_ATTR   131+ESYM_JVM_OFFSET


class NJavaConstant : public BSymbol {
public:
  NJavaConstant();
  virtual ~NJavaConstant();
  //
  virtual void debugDump();
  //
  const char *lookupString();
  //
  virtual ULONG getNameIndex() { return nameIndex; }
  //
//protected:
  //
  virtual void init();
  //
  UINT nameIndex;     // index into constants
  UINT otherIndex;
  UINT typeIndex;
  //
  char *theName;
  char *theType;
  char *theOther;
  //
};


#endif
