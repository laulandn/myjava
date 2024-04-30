#ifndef NICKVM_JAVAC_NJSTRING_H
#define NICKVM_JAVAC_NJSTRING_H


//#define NICKVM_STRINGS_ARE_OBJECTS 1


#ifdef NICKVM_STRINGS_ARE_OBJECTS
typedef __njstringInternal NJString;
#else
typedef char * NJString;
#endif


typedef NJString String;


#endif
