
#define DEBUG_OUT dBug
#define ERR_OUT std::cerr
//#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *debugOut
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cout
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream


/*

The name of this file is a bit of a misnomer...its more of a general Java
system call handler...and in fact, not even just Java...so maybe a better
name would be "system_call.cpp"...

NOTE: We assume a memory map with 2m of ram mapped at 0 and 2m of ram mapped
at the 2g mark. (What did I want it at the 2g mark for...?)
We'll put the stack at the 2m mark growing down.
We want a page fault for any unmapped memory (not just a no-op like usual)

*/


#include "EJavaVM.h"

#include "../../cpp/alib/adebug.h"
#include "../../cpp/alib/abasics.h"

#include "../../nemu/elib/EMapAbstract.h"

#include "../../nemu/cpulib/ecpu.h"


// Types of I/O Emulation
#define N_JAVA_IO_NONE    0x00
#define N_JAVA_IO_GENERIC 0x01


////////////////////////////////////////////////////////////////////////////////
//  EJavaVM Class
////////////////////////////////////////////////////////////////////////////////

EJavaVM::EJavaVM()
{
  DEBUG_OUT<<"EJavaVM constructor.\n";
  ioType=0;
  init();
}


EJavaVM::~EJavaVM()
{
  CONS_OUT<<"EJavaVM::~EJavaVM()\n";
  //if(!err.getError()) freeIO(); freeVideoMem();
  //err.setError();
}


void EJavaVM::init()
{
}


bool EJavaVM::recognizeName(const char *tname)
{
  const char *name=DSHELPER_alib.removeSpaces2(DSHELPER_alib.toLower(tname));
  if(!strcmp(name,"jvm")) return true;
  if(!strcmp(name,"java")) return true;
  if(!strcmp(name,"javaclassfile")) return true;
  if(!strcmp(name,"javabytecode")) return true;
  return false;
}


const char *EJavaVM::getName()
{
  switch(ioType) {
    case N_JAVA_IO_GENERIC:
      return "Java (generic)";
      break;
    default:
      return "Java (unknown)";
      break;
  }
}


// Note: No else on last one...
void EJavaVM::setKind(const char *tname)
{
  ioType=N_JAVA_IO_GENERIC;
  const char *name=DSHELPER_alib.removeSpaces2(DSHELPER_alib.toLower(tname));
  if(!strcmp(name,"jvm")) ioType=N_JAVA_IO_GENERIC;
  if(!strcmp(name,"java")) ioType=N_JAVA_IO_GENERIC;
  if(!strcmp(name,"javaclassfile")) ioType=N_JAVA_IO_GENERIC;
  if(!strcmp(name,"javabytecode")) ioType=N_JAVA_IO_GENERIC;
  initIO(ioType);
}


const char *EJavaVM::guessCpu(const char *tname)
{
  return "jvm";
}


void EJavaVM::initIO(uint8_t ttype)
{
  if(!ttype) return;
  freeIOAreas(); freeVideoMem();
  // Now init according to the system type
  ioType=ttype;
  switch(ioType) {
    case N_JAVA_IO_GENERIC:
      break;
    default:
      DEBUG_OUT<<"Unknown IO type!\n";
      ioType=N_JAVA_IO_NONE;
      //return;
      break;
  }
  mapIOAreas(); mapVideoMem();
  // Leave 256 bytes for underflow above stack...
  resetStack=0x200000-256;
}


void EJavaVM::resetEmu()
{
  if(myCpu) {
    myCpu->setResetStack(resetStack);
    myCpu->setStack(resetStack);
    myCpu->setFramePtr(resetStack);
    myCpu->setResetEntryPoint(resetEntryPoint);
    myCpu->jump(resetEntryPoint);
  }
}


bool EJavaVM::interp(const char *cmd,const char *a1,const char *a2,const char *a3)
{
  bool done=false;
  return done;
}


void EJavaVM::setMap(EMapAbstract *m)
{
  myMap=m;
  if(!m) return;
  if(strcmp("standard",m->getMapType())) {
    m->setPageFaults(true);
    m->setDemandPaging(true);
    m->setVirtualMemory(true);
  }
  //m->setWindow(w);
}


bool EJavaVM::systemCall(UINT num)
{
  ERR_OUT<<"EJavaVM::systemCall("<<ALIB2HEX4(num)<<"), we didn't handle it.\n";
  return false;
}



void EJavaVM::loadInitialClass()
{
  DEBUG_OUT<<"loadInitialClass...nothing here!\n";
}

