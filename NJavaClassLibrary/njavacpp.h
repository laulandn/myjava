#ifndef NJCLASSLIB_JAVACPP_H
#define NJCLASSLIB_JAVACPP_H


// TODO: This needs either major cleanup or to go away!!!
// NOTE: It looks like a lot of things here need to be moved to class .h's


//
//
// This is part of an implementation in C++ of the standard Java libraries.
// It includes only the bare functionaltity needed for basic programs.
//
//

/*
Fun Java things to remember when translating to C++:
* data members are initialized to 0
* consts can be defined per class
* there are true class (vs instance) members
* sizeof an array actually works
*/


#define DEBUG_VERBOSE 1


//#define NEMU_USE_JNI 1

#define NICK_USE_GUILIB 1

#define NICK_NEW_JAVA_CLASSLIB 1


#ifdef NICK_NEW_JAVA_CLASSLIB
#define NICK_ADD_THE_J 1
//#define NICK_UPPER2LOWER_J 1
#define NICK_ADD_CONST_PREFIX 1
#define NICK_STUPID_GLOBAL_FUNCS 1
#endif


#include <stdio.h>
#include <string.h>

#ifdef OLD_COMPILER
#include <iostream.h>
#else
#include <iostream>
#endif


#include "../../cpp/alib/abaseclass.h"
#ifdef DEBUG
#include "../../cpp/alib/adebug.h"
#endif // DEBUG


#ifdef NEMU_USE_JNI
#include <jni.h>
#endif


#include "njtypes.h"


/************
*************    GLOBALS
************/


#ifdef NICK_STUPID_GLOBAL_FUNCS
class Thread;
extern Thread *Thread_currentThread();
extern double jMath_pow(double a,double b);
extern void jSystem_arraycopy(float *src, int srcPos, float *dest, int destPos, int length);
extern void jSystem_arraycopy(int *src, int srcPos, int *dest, int destPos, int length);
#endif // NICK_STUPID_GLOBAL_FUNC


// Kludge for global System object (not static funcs yet), implicitly defined...
#include "java/lang/System.h"


/************
*************    CONSTANTS
************/


#ifdef NICK_ADD_CONST_PREFIX
//
#define MIN_PRIORITY Thread_MIN_PRIORITY
#define STATE_INITED Thread_STATE_INITED
#define STATE_STOPPED Thread_STATE_STOPPED
#define STATE_STARTED Thread_STATE_STARTED
#define STATE_RUNNING Thread_STATE_RUNNING
#define STATE_WAITING Thread_STATE_WAITING
//
#define TT_EOL jStreamTokenizer_TT_EOL
#define TT_EOF jStreamTokenizer_TT_EOF
#define TT_WORD jStreamTokenizer_TT_WORD
#define TT_NUMBER jStreamTokenizer_TT_NUMBER
//
#endif


#endif

