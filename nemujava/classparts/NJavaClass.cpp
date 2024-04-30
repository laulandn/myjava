
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


//#ifdef NEMU_INCLUDE_JAVA


#include <iostream>


#include "NJavaClass.h"

#include "NJavaAttribute.h"
#include "NJavaCode.h"
#include "NJavaField.h"
#include "NJavaInterface.h"
#include "NJavaMethod.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaClass Class
////////////////////////////////////////////////////////////////////////////////

NJavaClass::NJavaClass()
{
  DEBUG_OUT<<"NJavaClass::NJavaClass()...\n";
  init();
}


NJavaClass::NJavaClass(char const *filename)
{
  DEBUG_OUT<<"NJavaClass::NJavaClass("<<filename<<")...\n";
  init();
  DEBUG_OUT<<"Not implemented!\n";
  exit(EXIT_FAILURE);
}


NJavaClass::~NJavaClass()
{
}


void NJavaClass::init()
{
  numInterfaces=0;
  numFields=0;
  numMethods=0;
  numAttributes=0;
  numConstants=0;
  //
  thisClass=0; superClass=0;
  accessFlags=0;
  minorVersion=0; majorVersion=0;
  name=NULL;
}


void NJavaClass::printNameType(unsigned int snum)
{
  if(!validateConstant(snum)) return;
  unsigned int nameConst=lookupConstant(snum)->getNameIndex();
  unsigned int typeConst=0/*constants[snum].getVal3()*/;
  if(typeConst) { DEBUG_OUT<<lookupConstantString(typeConst)<<":"; }
  if(nameConst) { DEBUG_OUT<<lookupConstantString(nameConst)<<" "; }
  DEBUG_OUT<<"\n";
}


const char *NJavaClass::lookupConstantString(unsigned int c)
{
  if(!validateConstant(c)) return NULL;
  return lookupConstant(c)->lookupString();
}


NJavaConstant *NJavaClass::lookupConstant(unsigned int c)
{
  if(!validateConstant(c)) return NULL;
  unsigned int t=1;
  constants.jumpToHead();
  bool reading=true;
  while(reading) {
    if(t==c) return (NJavaConstant *)constants.info();
    else { constants.advance(); t++; }
  }
  return NULL;
}


bool NJavaClass::validateConstant(unsigned int c)
{
  if(c<numConstants) {
    //if(!constants[c]) {
    //  DEBUG_OUT<<"validateConstant NULL constant number "<<c<<"!\n";
    //  return false;
    //}
  }
  else {
    DEBUG_OUT<<"validateConstant bad constant number "<<c<<"!\n";
    return false;
  }
  return true;
}


void NJavaClass::debugDump()
{
  DEBUG_OUT<<"Classfile "<<name<<"\n";
  DEBUG_OUT<<"  Last modified XXX\n";
  DEBUG_OUT<<"  MD5 checksum XXX\n";
  DEBUG_OUT<<"  thisClass="<<thisClass<<"\n";
  DEBUG_OUT<<"superClass="<<superClass<<"\n";
  DEBUG_OUT<<"public class  XXX\n";
  DEBUG_OUT<<"  SourceFile: "<<name<<"\n";
  DEBUG_OUT<<"  minor version: "<<minorVersion<<"\n";
  DEBUG_OUT<<"  major version: "<<majorVersion<<"\n";
  DEBUG_OUT<<"  flags: "<<accessFlags<<"\n";
  unsigned int n=0;
  DEBUG_OUT<<"numInterfaces="<<numInterfaces<<"\n";
  interfaces.jumpToHead();
  while(!interfaces.atEnd()) {
    DEBUG_OUT<<"interfaces #"<<n<<"\n";
    NJavaInterface *theObj=NULL;
    interfaces.advance();
    n++;
  }
  DEBUG_OUT<<"\n";
  //
  n=0;
  DEBUG_OUT<<"numFields="<<numFields<<"\n";
  fields.jumpToHead();
  while(!fields.atEnd()) {
    DEBUG_OUT<<"fields #"<<n<<"\n";
    NJavaField *theObj=NULL;
    fields.advance();
    n++;
  }
  DEBUG_OUT<<"\n";
  //
  n=0;
  DEBUG_OUT<<"numMethods="<<numMethods<<"\n";
  methods.jumpToHead();
  while(!methods.atEnd()) {
    DEBUG_OUT<<"methods #"<<n<<"\n";
    NJavaMethod *theObj=NULL;
    methods.advance();
    n++;
  }
  DEBUG_OUT<<"\n";
  //
  n=0;
  DEBUG_OUT<<"codes...\n";
  codes.jumpToHead();
  while(!codes.atEnd()) {
    DEBUG_OUT<<"codes #"<<n<<"\n";
    NJavaCode *theObj=NULL;
    codes.advance();
    n++;
  }
  DEBUG_OUT<<"\n";
  //
  n=0;
  DEBUG_OUT<<"numAttributes="<<numAttributes<<"\n";
  attributes.jumpToHead();
  while(!attributes.atEnd()) {
    DEBUG_OUT<<"attributes #"<<n<<"\n";
    NJavaAttribute *theObj=NULL;
    attributes.advance();
    n++;
  }
  DEBUG_OUT<<"\n";
  //
  n=0;
  DEBUG_OUT<<"Constant pool:\n";
  for(n=1;n<numConstants+1;n++) {
    NJavaConstant *theObj=lookupConstant(n);
    //dumpConstant(theObj);
    //theObj->debugDump();
  }
}


//#endif
