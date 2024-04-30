#ifndef NICKVM_JAVAC_NJSTRINGINTERNAL_H
#define NICKVM_JAVAC_NJSTRINGINTERNAL_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../../cpp/alib/abaseclass.h"
#ifdef DEBUG
#include "../../../cpp/alib/adebug.h"
#endif // DEBUG


class __njstringInternal : public ABaseClass {
public:
  __njstringInternal();
  __njstringInternal(char *s);
  //
  bool _nickvm_String_is_null() { if(theStringVal) return false; else return true; }
  char *_nickvm_String_charptr() { return theStringVal; }
  //
protected:
  char *theStringVal;
};


// global "NULL" string object
extern __njstringInternal __njstringInternal_NULL;


#endif
