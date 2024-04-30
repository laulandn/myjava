#ifndef NJCLASSFILE_NJAVACLASS_H
#define NJCLASSFILE_NJAVACLASS_H


#ifdef NEMU_INCLUDE_JAVA


#include "../../../cpp/alib/abasics.h"

#include "../../../nemu/binarylib/BClassObject.h"

#include "NJavaConstant.h"


class NJavaClass : public BClassObject {
public:
  NJavaClass();
  NJavaClass(const char *theName);
  // NOTE: Params match the first two letters in the order they appear as data members below
  // OLD NJavaClass(UINT th,UINT su,UINT ac,AList_alib *in,AList_alib *fi,AList_alib *me,AList_alib *at,AList_alib *co);
  //
  virtual ~NJavaClass();
  //
  virtual void debugDump();
  //
//protected:
  //
  virtual void init();
  //void dumpConstant(BSymbol *sym);
  virtual void printNameType(unsigned int snum);
  virtual const char *lookupConstantString(unsigned int c);
  virtual bool validateConstant(unsigned int c);
  //
  NJavaConstant *lookupConstant(unsigned int c);
  //
};


#endif


#endif
