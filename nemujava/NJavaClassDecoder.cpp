
#ifdef BUILDING_NEMU
#define ERR_OUT nemuConsole
#define CONS_OUT nemuConsole
#define CONS_IN nemuConsole
#else
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#endif
#define DEBUG_OUT dBug


#include "../../cpp/alib/adebug.h"
#include "../../cpp/alib/abasics.h"

#include "NJavaClassDecoder.h"

#include "../../nemu/binarylib/BSection.h"

#include "../../nemu/cpulib/ecpu.h"

#include "../../nemu/elib/nld.h"
#include "../../nemu/elib/EMapTrivial.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


#ifdef NEMU_INCLUDE_JAVA


////////////////////////////////////////////////////////////////////////////////
//  NJavaClassDecoder Class
////////////////////////////////////////////////////////////////////////////////

/* STATIC */
bool NJavaClassDecoder::recognize(unsigned char *buffer,const char *fname)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"NJavaClassDecoder looking for signature...\n";
#endif
  bool ret=false;
  if(!buffer) { ERR_OUT<<"No buffer!  Giving up!\n"; return ret; }
  if((buffer[0]==0xca)&&(buffer[1]==0xfe)&&(buffer[2]==0xba)&&(buffer[3]==0xbe)) {
    // Next to check that it isn't a mutli-arch Mach-O file.
    //if((buffer[8])||(buffer[9])) return true;
    ret=true;
  }
  /*
  DEBUG_OUT<<"These characters did not match:\n";
  for(UINT t=0;t<4;t++) DEBUG_OUT<<"buffer["<<t<<"]=\'"<<buffer[t]<<"\'\n";
  */
  /*
  if((buffer[2]=='P')&&(buffer[3]=='K')) {
    // may be a ZIP/JAR file, look inside for java classes...
  }
  */
  if(ret) { DEBUG_OUT<<"(recognized)\n"; } else { DEBUG_OUT<<"(it was not recognized!)\n"; }
  return ret;
}


NJavaClassDecoder::NJavaClassDecoder(const char *fname) : BBinaryDecoder(fname)
{
  init();
  theCurrentOffset=0;
  /*
  numConstants=0;  numInterfaces=0;  numFields=0;
  numMethods=0;  numAttributes=0;
  lastConstant=0;
  */
  lastUsedAddress=0;
  /*
  thisClass=0;  superClass=0;  accessFlags=0;
  */
  if(!readBinary(fname)) { ERR_OUT<<"NJavaClassDecoder readBinary() failed!\n"; exit(EXIT_FAILURE); }
  else { DEBUG_OUT<<"NJavaClassDecoder readBinary succeeded!\n"; }
  if(!verifyOkay()) { ERR_OUT<<"NJavaClassDecoder verifyOkay() failed!\n"; exit(EXIT_FAILURE); }
  else { DEBUG_OUT<<"NJavaClassDecoder verifyOkay succeeded!\n"; }
  if(!decodeBinary()) { ERR_OUT<<"NJavaClassDecoder decodeBinary() failed!\n"; exit(EXIT_FAILURE); }
  else { DEBUG_OUT<<"NJavaClassDecoder decodeBinary succeeded!\n"; }
  DEBUG_OUT<<"NJavaClassDecoder::NJavaClassDecoder('"<<fname<<"') done.\n";
}


NJavaClassDecoder::~NJavaClassDecoder()
{
}


void NJavaClassDecoder::init()
{
  //theClass=NULL;
}


const char *NJavaClassDecoder::whichCPUName()
{
  return "javabytecode";
}


const char *NJavaClassDecoder::whichIOType()
{
  return "javaclassfile";
}


// TODO: There should be more useful stuff to check here...
bool NJavaClassDecoder::verifyOkay()
{
  DEBUG_OUT<<"NJavaClassDecoder verify...\n";
  if(!checkSanityNotBinaryImage()) { CONS_OUT<<"verifyOkay failed!\n";  exit(EXIT_FAILURE); return false; }
  bool ret=false;
  //ld->reset();
  /*
  if((binaryImage[0]==0xca)&&(binaryImage[1]==0xfe)&&(binaryImage[2]==0xba)&&(binaryImage[3]==0xbe))
  {
    //arch=N_LD_ARCH_JAVA;
    //ret=true;
  }
  */
  /*
  if(!ret) {
    CONS_OUT<<"File is not in Java Class format!\n";
    exit(EXIT_FAILURE);
    return false;
  }
  */
  ret=true;
  return ret;
}


bool NJavaClassDecoder::decodeBinary()
{
  DEBUG_OUT<<"NJavaClassDecoder::decodeBinary()\n";
  if(!memBlock) {
    CONS_OUT<<"memBlock is NULL!\n";
    exit(EXIT_FAILURE);
    return false;
  }
  theCurrentOffset=getLoadAddress();
  DEBUG_OUT<<"binary is at "<<ALIB2HEX8(theCurrentOffset)<<"\n";
  ULONG cafeBabeSig=memBlock->read32b(theCurrentOffset);
  DEBUG_OUT<<"cafeBabeSig is "<<ALIB2HEX8(cafeBabeSig)<<"\n";
  if((memBlock->read8(theCurrentOffset)==0xca)&&(memBlock->read8(theCurrentOffset+1)==0xfe)&&(memBlock->read8(theCurrentOffset+2)==0xba)&&(memBlock->read8(theCurrentOffset+3)==0xbe)) {
    DEBUG_OUT<<"signature is correct\n";
  }
  else { CONS_OUT<<"signature is incorrect!  Giving up!\n"; exit(EXIT_FAILURE); return false; }
  UINT signature=memBlock->read32b(theCurrentOffset);  theCurrentOffset+=4;
  DEBUG_OUT<<"signature="<<DSHELPER_alib.myHex(signature)<<"\n";
  //
  DEBUG_OUT<<"Going to create NJavaClass...\n";
  theClass=new NJavaClass();
  if(!theClass) { CONS_OUT<<"couldn't alloc theClass!\n"; exit(EXIT_FAILURE); return false; }
  //
  theClass->minorVersion=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  theClass->majorVersion=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  DEBUG_OUT<<"majorVersion="<<theClass->majorVersion<<"  minorVersion="<<theClass->minorVersion<<"\n";
  //
  //DEBUG_OUT<<"\n";
  UINT numConsts=memBlock->read16b(theCurrentOffset)-1;  theCurrentOffset+=2;
  DEBUG_OUT<<"numConsts is "<<numConsts<<"\n";
  theClass->numConstants=numConsts;
  if(!readConstants(numConsts)) { DEBUG_OUT<<"(readConstants didn't)\n"; return false; }
  DEBUG_OUT<<"(Done reading consts)\n";
  //
  //DEBUG_OUT<<"\n";
  theClass->accessFlags=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  // NOTE: 0x001=public 0x010=final 0x020=super 0x200=interface 0x400=abstract
  DEBUG_OUT<<"accessFlags="<<theClass->accessFlags<<" ";
  if(theClass->accessFlags&0x01) DEBUG_OUT<<"public ";
  if(theClass->accessFlags&0x010) DEBUG_OUT<<"final ";
  if(theClass->accessFlags&0x020) DEBUG_OUT<<"super ";
  if(theClass->accessFlags&0x200) DEBUG_OUT<<"interface ";
  if(theClass->accessFlags&0x400) DEBUG_OUT<<"abstract ";
  DEBUG_OUT<<"\n";
  //
  theClass->thisClass=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  theClass->superClass=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  NJavaConstant *theConst=NULL;
  //
  theConst=theClass->lookupConstant(theClass->thisClass);
  if(!theConst) { DEBUG_OUT<<"No const for class!\n"; exit(EXIT_FAILURE); }
  DEBUG_OUT<<"thisClass("<<theClass->thisClass<<")='"<<theConst->theName<<"'\n";
  //
  theConst=theClass->lookupConstant(theClass->superClass);
  if(!theConst) { DEBUG_OUT<<"No const for superClass!\n"; exit(EXIT_FAILURE); }
  DEBUG_OUT<<"superClass("<<theClass->superClass<<")='"<<theConst->theName<<"'\n";
  //
  theClass->numInterfaces=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  if(!decodeInterfaces()) { DEBUG_OUT<<"(decodeInterfaces didn't)\n"; return false; }
  //
  theClass->numFields=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  if(!decodeFields()) { DEBUG_OUT<<"(decodeFields didn't)\n"; return false; }
  //
  theClass->numMethods=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  if(!decodeMethods()) { DEBUG_OUT<<"(decodeMethods didn't)\n"; return false; }
  //
  //DEBUG_OUT<<"\n";
  theClass->numAttributes=memBlock->read16b(theCurrentOffset);  theCurrentOffset+=2;
  if(!decodeAttributes()) { DEBUG_OUT<<"(decodeAttributes didn't)\n"; return false; }
  //
  if(!checkSanity()) { DEBUG_OUT<<"NJavaClassDecoder::decodeBinary() checkSanity failed, giving up!\n"; exit(EXIT_FAILURE); }
  //ld->reset();
  //if(n) ld->getSegment()->getSections()->append(n);
  //else { CONS_OUT<<"Didn't get NRunnableCode!\n"; exit(EXIT_FAILURE); }
  return true;
}


bool NJavaClassDecoder::readConstants(UINT numConsts)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readConstants("<<numConsts<<")\n";
#endif
  if(!numConsts) { DEBUG_OUT<<"(no constants, returning)\n"; return true; }
  UINT t=1;
  bool reading=true;
  NJavaConstant *theConst=NULL;
  while(reading) {
    //DEBUG_OUT<<"new BSymbol...\n";
    NJavaConstant *theConst=new NJavaConstant();
    //
    //DEBUG_OUT<<"Going to readConstantAtOffset...\n";
    UINT newOffset=readConstantAtOffset(theConst,theCurrentOffset);
    DEBUG_OUT<<"Constant #"<<t;
    DEBUG_OUT<<" addr="<<ALIB2HEX8(theConst->getAddress());
    DEBUG_OUT<<" size="<<theConst->getSize();
    DEBUG_OUT<<" val1="<<theConst->getVal1();
    DEBUG_OUT<<" val2="<<theConst->getVal2();
    DEBUG_OUT<<" val3="<<theConst->getVal3();
    DEBUG_OUT<<" ";
    char *theName=NULL;
    switch(theConst->getSymType()) {
      case ESYM_JVM_UTF8:
        DEBUG_OUT<<"UTF8";
        getTmpZeroStrAtOffset(theConst->getVal1(),theConst->getSize());
        theName=strdup(tempString);
        break;
      case ESYM_JVM_INT:
        DEBUG_OUT<<"INT";
        break;
      case ESYM_JVM_FLOAT:
        DEBUG_OUT<<"FLOAT";
        break;
      case ESYM_JVM_LONG:
        DEBUG_OUT<<"LONG";
        break;
      case ESYM_JVM_DOUBLE:
        DEBUG_OUT<<"DOUBLE";
        break;
      case ESYM_JVM_CLASS:
        DEBUG_OUT<<"CLASS";
        break;
      case ESYM_JVM_STRING:
        DEBUG_OUT<<"STRING";
        break;
      case ESYM_JVM_FIELD:
        DEBUG_OUT<<"FIELD";
        break;
      case ESYM_JVM_METHOD:
        DEBUG_OUT<<"METHOD";
        break;
      case ESYM_JVM_INTERFACE:
        DEBUG_OUT<<"INTERFACE";
        break;
      case ESYM_JVM_NAMETYPE:
        DEBUG_OUT<<"NAMETYPE";
        break;
      default:
        DEBUG_OUT<<"Unknown\n";
        DEBUG_OUT<<"Invalid constant type...giving up...\n";
        exit(EXIT_FAILURE);
        break;
    }
    DEBUG_OUT<<"\n";
    theConst->setSymbolName(theName);
    if(mySymtab) {
      AList_alib *strings=mySymtab->getStringList();
      if(strings) strings->append((void *)theConst);
    }
    theConst->otherIndex=theConst->getVal2();
    theConst->typeIndex=theConst->getVal3();
    theClass->constants.append((void *)theConst);
    t++;
    if(t>numConsts) reading=false;
    theCurrentOffset+=newOffset;
  }
  fixContantNames();
  goBackAndFixMoreNames();
  return true;
}


void NJavaClassDecoder::fixContantNames()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"fixContantNames()\n";
#endif
  //DEBUG_OUT<<"There should be "<<theClass->getNumConstants()<<" constants.\n";
  bool reading=true;
  char *theName=NULL;
  char *otherName=NULL;
  char *typeName=NULL;
  AList_alib *theSymList=mySymtab->getStringList();
  theSymList->jumpToHead();
  BSymbol *sym;
  unsigned int t=1;
  while(reading) {
    tempString[0]=0;
    sym=(BSymbol *)theSymList->info();
    theName=NULL;
    otherName=NULL;
    typeName=NULL;
    //
    DEBUG_OUT<<"Constant #"<<t;
    DEBUG_OUT<<" ";
    unsigned long theNameIndex=sym->getVal1();
    unsigned long theOtherIndex=sym->getVal2();
    unsigned long theTypeIndex=sym->getVal3();
    bool skip=false;
    switch(sym->getSymType()) {
      case ESYM_JVM_UTF8:
        DEBUG_OUT<<"UTF8";
        theName=(char *)sym->getSymbolName();
        theNameIndex=0;
        skip=true;
        break;
      case ESYM_JVM_INT:
        DEBUG_OUT<<"INT";
        break;
      case ESYM_JVM_FLOAT:
        DEBUG_OUT<<"FLOAT";
        break;
      case ESYM_JVM_LONG:
        DEBUG_OUT<<"LONG";
        break;
      case ESYM_JVM_DOUBLE:
        DEBUG_OUT<<"DOUBLE";
        break;
      case ESYM_JVM_CLASS:
        DEBUG_OUT<<"CLASS";
        readNameStringConstAtIndex(tempString,theTypeIndex);
        theName=strdup(tempString);
        break;
      case ESYM_JVM_STRING:
        DEBUG_OUT<<"STRING";
        readNameStringConstAtIndex(tempString,theNameIndex);
        theName=strdup(tempString);
        sym->setSize(strlen(theName));
        break;
      case ESYM_JVM_FIELD:
        DEBUG_OUT<<"FIELD";
        readNameStringConstAtIndex(tempString,theNameIndex);
        theName=strdup(tempString);
        readNameStringConstAtIndex(tempString,theOtherIndex);
        otherName=strdup(tempString);
        break;
      case ESYM_JVM_METHOD:
        DEBUG_OUT<<"METHOD";
        readNameStringConstAtIndex(tempString,theNameIndex);
        theName=strdup(tempString);
        readNameStringConstAtIndex(tempString,theOtherIndex);
        otherName=strdup(tempString);
        break;
      case ESYM_JVM_INTERFACE:
        DEBUG_OUT<<"INTERFACE";
        readNameStringConstAtIndex(tempString,theOtherIndex);
        theName=strdup(tempString);
        readNameStringConstAtIndex(tempString,theNameIndex);
        otherName=strdup(tempString);
        break;
      case ESYM_JVM_NAMETYPE:
        DEBUG_OUT<<"NAMETYPE";
        // Yes it's backwards
        readNameStringConstAtIndex(tempString,theNameIndex);
        typeName=strdup(tempString);
        readNameStringConstAtIndex(tempString,theTypeIndex);
        theName=strdup(tempString);
        break;
      default:
        DEBUG_OUT<<"Unknown\n";
        DEBUG_OUT<<"Invalid constant type...giving up...\n";
        exit(EXIT_FAILURE);
        break;
    }
    if(typeName) DEBUG_OUT<<" typeName("<<theTypeIndex<<")='"<<typeName<<"'";
    if(theName) DEBUG_OUT<<" theName("<<theNameIndex<<")='"<<theName<<"'";
    if(otherName) DEBUG_OUT<<" otherName("<<theOtherIndex<<")='"<<otherName<<"'";
    DEBUG_OUT<<"\n";
    if(!skip) {
      sym->setSymbolName(theName);
      NJavaConstant *theConst=theClass->lookupConstant(t);
      if(theConst) {
        if(theName) { theConst->theName=strdup(theName); theConst->nameIndex=theNameIndex; }
        if(otherName) { theConst->theOther=strdup(otherName); theConst->typeIndex=theTypeIndex; }
        if(typeName) { theConst->theType=strdup(typeName); theConst->otherIndex=theOtherIndex; }
      }
    }
    theSymList->advance();
    t++;
    if(theSymList->atEnd()) reading=false;
  }
  return;
}


void NJavaClassDecoder::goBackAndFixMoreNames()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"goBackAndFixMoreNames()\n";
#endif
  //DEBUG_OUT<<"There should be "<<theClass->getNumConstants()<<" constants.\n";
  bool reading=true;
  char *theName=NULL;
  char *otherName=NULL;
  char *typeName=NULL;
  AList_alib *theSymList=mySymtab->getStringList();
  theSymList->jumpToHead();
  BSymbol *sym;
  unsigned int t=1;
  while(reading) {
    tempString[0]=0;
    sym=(BSymbol *)theSymList->info();
    theName=NULL;
    otherName=NULL;
    typeName=NULL;
    //
    unsigned long theNameIndex=sym->getVal1();
    unsigned long theOtherIndex=sym->getVal2();
    unsigned long theTypeIndex=sym->getVal3();
    bool skip=true;
    if(sym->getSymType()==ESYM_JVM_METHOD) skip=false;
    if(sym->getSymType()==ESYM_JVM_FIELD) skip=false;
    if(!skip) {
      if(sym->getSymType()==ESYM_JVM_METHOD) DEBUG_OUT<<"METHOD";
      if(sym->getSymType()==ESYM_JVM_FIELD) DEBUG_OUT<<"FIELD";
      DEBUG_OUT<<" #"<<t;
      NJavaConstant *theConst=theClass->lookupConstant(theNameIndex);
      theTypeIndex=theConst->typeIndex;
      readNameStringConstAtIndex(tempString,theTypeIndex);
      typeName=strdup(tempString);
      theConst=theClass->lookupConstant(theOtherIndex);
      theOtherIndex=theConst->nameIndex;
      readNameStringConstAtIndex(tempString,theOtherIndex);
      otherName=strdup(tempString);
      theTypeIndex=theConst->typeIndex;
      readNameStringConstAtIndex(tempString,theTypeIndex);
      theName=strdup(tempString);
      if(sym->getSymType()==ESYM_JVM_METHOD) {
        if(typeName) DEBUG_OUT<<" '"<<typeName<<"' ::";
        if(theName) DEBUG_OUT<<" '"<<theName<<"'";
        if(otherName) DEBUG_OUT<<" ('"<<otherName<<"')";
      }
      if(sym->getSymType()==ESYM_JVM_FIELD) {
        // TODO: type is super, other is type!
        if(typeName) DEBUG_OUT<<" '"<<typeName<<"' ::";
        if(otherName) DEBUG_OUT<<" '"<<otherName<<"'";
        if(theName) DEBUG_OUT<<" '"<<theName<<"'";
      }
     DEBUG_OUT<<"\n";
    }
    theSymList->advance();
    t++;
    if(theSymList->atEnd()) reading=false;
  }
  return;
}


// Since interfaces aren't implemented yet, this is really just placeholder
bool NJavaClassDecoder::decodeInterfaces()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"decodeInterfaces(): numInterfaces="<<theClass->numInterfaces<<"\n";
#endif
  if(!theClass->numInterfaces) { /*DEBUG_OUT<<"(no interfaces)\n";*/ return true; }
  UINT t=1;
  bool reading=true;
  NJavaInterface *anInterface=NULL;
  while(reading) {
    anInterface=new NJavaInterface();
    //
    UINT newOffset=readInterfaceAtOffset(anInterface,theCurrentOffset);
    DEBUG_OUT<<"Interface #"<<t<<" addr="<<ALIB2HEX8(anInterface->getAddress());
    //getNameStringAtOffset(tempString,anInterface.name);
    //DEBUG_OUT<<" name="<<a.name;
    strcpy(tempString,"unknown interface");
    DEBUG_OUT<<" '"<<tempString<<"'\n";
    //getNameStringAtOffset(tempString,anInterface.name);
    strcpy(tempString,"unknown interface");
    DEBUG_OUT<<"Creating symbol...\n";
    anInterface->setNum(t);
    theClass->interfaces.append((void *)anInterface);
    if(mySymtab) {
      AList_alib *symbols=mySymtab->getSymList();
      if(symbols) symbols->append((void *)anInterface);
     }
    else { CONS_OUT<<"memBlock doesn't have a symbol table! Giving up!\n"; exit(EXIT_FAILURE); return false; }
    //theCurrentOffset+=6;
    //theCurrentOffset+=anInterface.len;
    t++;
    if(t>theClass->numInterfaces) reading=false;
  }
  return true;
}


// Since interfaces aren't implemented yet, this is really just placeholder
bool NJavaClassDecoder::decodeFields()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"decodeFields(): numFields="<<theClass->numFields<<"\n";
#endif
  if(!theClass->numFields) { /*DEBUG_OUT<<"(no fields)\n";*/ return true; }
  UINT t=1;
  bool reading=true;
  NJavaField *aField=NULL;
  while(reading) {
    aField=new NJavaField();
    UINT newOffset=readFieldAtOffset(aField,theCurrentOffset);
    DEBUG_OUT<<"Field #"<<t<<" addr="<<ALIB2HEX8(aField->getAddress());
    //getNameStringAtOffset(tempString,aField.name);
    //DEBUG_OUT<<" name="<<a.name;
    strcpy(tempString,"unknown field");
    DEBUG_OUT<<" '"<<tempString<<"'\n";
    //getNameStringAtOffset(tempString,aField.name);
    strcpy(tempString,"unknown field");
    DEBUG_OUT<<"Creating symbol...\n";
    aField->setNum(t);
    theClass->fields.append((void *)aField);
    if(mySymtab) {
      AList_alib *symbols=mySymtab->getSymList();
      if(symbols) symbols->append((void *)aField);
     }
    else { CONS_OUT<<"memBlock doesn't have a symbol table! Giving up!\n"; exit(EXIT_FAILURE); return false; }
    //theCurrentOffset+=6;
    //theCurrentOffset+=aField.len;
    t++;
    if(t>theClass->numFields) reading=false;
  }
  return true;
}


// TODO: What are the flags?
bool NJavaClassDecoder::decodeMethods()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"decodeMethods(): numMethods="<<theClass->numMethods<<"\n";
#endif
  if(!theClass->numMethods) { DEBUG_OUT<<"(no methods)\n"; return true; }
  UINT t=1;
  bool reading=true;
  NJavaMethod *aMethod=NULL;
  while(reading) {
    UINT theFlagsM=0;
    UINT theNameIndexM=0;
    UINT thedescM=0;
    UINT theNumAttributesM=0;
    aMethod=new NJavaMethod();
    UINT newOffset=readConstantAtOffset(aMethod,theCurrentOffset);
    tempString[0]=0;
    DEBUG_OUT<<"Method #"<<t<<" addr="<<ALIB2HEX8(aMethod->getAddress())<<" flags="<<theFlagsM;
    readNameStringConstAtIndex(tempString,theNameIndexM);
    //DEBUG_OUT<<" name="<<m.name;
    DEBUG_OUT<<" '"<<tempString<<"' isa";
    readNameStringConstAtIndex(tempString,thedescM);
    //DEBUG_OUT<<" desc="<<m.desc;
    DEBUG_OUT<<" '"<<tempString<<"'";
    //DEBUG_OUT<<" # of codes="<<m.num;
    DEBUG_OUT<<"\n";
    theCurrentOffset+=8;
    for(UINT i=0;i<theNumAttributesM;i++) {
      UINT theNameIndexA=0;
      UINT theLenA=0;
      //
      UINT theAddressC=0;
      UINT theNameIndexC=0;
      UINT theLenC=0;
      UINT theStackMaxC=0;
      UINT theLocalsMaxC=0;
      UINT theCodeAddrC=0;
      UINT theCodeLenC=0;
      UINT theExceptionAddrC=0;
      UINT theExceptionLenC=0;
      UINT theAttribAddrC=0;
      UINT theNumAttribsC=0;
      //
      //DEBUG_OUT<<"new BSymbol...\n";
      BSymbol *asym=new BSymbol();
      //
      UINT newOffset=readAttributeAtOffset(asym,theCurrentOffset);
      tempString[0]=0;
      newOffset+=readNameStringConstAtIndex(tempString,theNameIndexA);
      if(!strcmp(tempString,"Code")) {
        //
        //DEBUG_OUT<<"new BSymbol...\n";
        BSymbol *csym=new BSymbol();
        //
        readCodeAtOffset(csym,theCurrentOffset);
        DEBUG_OUT<<"code #"<<i<<" for method #"<<t;
        DEBUG_OUT<<" addr="<<ALIB2HEX8(theAddressC);
        //DEBUG_OUT<<" name="<<c.name;
        readNameStringConstAtIndex(tempString,theNameIndexC);
        DEBUG_OUT<<" '"<<tempString<<"'";
        DEBUG_OUT<<" stackMax="<<theStackMaxC;
        DEBUG_OUT<<" localsMax="<<theLocalsMaxC;
        DEBUG_OUT<<"\n";
        DEBUG_OUT<<"codeLen="<<theCodeLenC;
        DEBUG_OUT<<" codeAddr="<<ALIB2HEX8(theCodeAddrC);
        DEBUG_OUT<<"\n";
        DEBUG_OUT<<"exceptionLen="<<theExceptionLenC;
        DEBUG_OUT<<" exceptionAddr="<<ALIB2HEX8(theExceptionAddrC);
        DEBUG_OUT<<"\n";
        DEBUG_OUT<<"numAttrib="<<theNumAttribsC;
        DEBUG_OUT<<" attribAddr="<<ALIB2HEX8(theAttribAddrC);
        DEBUG_OUT<<"\n";
        readNameStringConstAtIndex(tempString,theNameIndexM);
        csym->setNum(t);
        if(mySymtab) {
          AList_alib *symbols=mySymtab->getSymList();
          if(symbols) symbols->append((void *)csym);
        }
        else { CONS_OUT<<"memBlock doesn't have a symbol table! Giving up!\n"; exit(EXIT_FAILURE); return false; }
      }
      else {
        UINT theAddressAA=0;
        UINT theLenAA=0;
        UINT theNameIndexAA=0;
        UINT theDataAA=0;
        //
        //DEBUG_OUT<<"new BSymbol...\n";
        BSymbol *aasym=new BSymbol();
        //
        UINT newOffset=readAttributeAtOffset(asym,theCurrentOffset);
        DEBUG_OUT<<"-Attribute #"<<i<<" addr="<<DSHELPER_alib.myHex(theAddressAA)<<" len="<<theLenAA;
        DEBUG_OUT<<" data="<<theDataAA;
        DEBUG_OUT<<" nameIndex="<<theNameIndexAA<<" "<<tempString;
        DEBUG_OUT<<"\n";
        readNameStringConstAtIndex(tempString,theNameIndexAA);
        asym->setNum(t);
        if(mySymtab) {
          AList_alib *symbols=mySymtab->getSymList();
          if(symbols) symbols->append((void *)aasym);
        }
      }
    }
    aMethod->setNum(t);
    theClass->methods.append((void *)aMethod);
    if(mySymtab) {
      AList_alib *symbols=mySymtab->getSymList();
      if(symbols) symbols->append((void *)aMethod);
    }
    //theCurrentOffset+=6;
    //theCurrentOffset+=anAttribute->getSize();
    t++;
    if(t>theClass->numMethods) reading=false;
  }
  return true;
}


bool NJavaClassDecoder::decodeAttributes()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"decodeAttributes(): numAttributes="<<theClass->numAttributes<<"\n";
#endif
  if(!theClass->numAttributes) { DEBUG_OUT<<"(no attributes)\n"; return true; }
  UINT t=1;
  NJavaAttribute *anAttribute=NULL;
  bool reading=true;
  while(reading) {
    UINT theNameIndex=0;
    UINT theData=0;
    anAttribute=new NJavaAttribute();
    UINT newOffset=readAttributeAtOffset(anAttribute,theCurrentOffset);
    DEBUG_OUT<<"Attribute #"<<t<<" addr="<<ALIB2HEX8(anAttribute->getAddress());
    DEBUG_OUT<<" len="<<anAttribute->getSize();
    DEBUG_OUT<<" data="<<anAttribute->getData();
    readNameStringConstAtIndex(tempString,theNameIndex);
    //DEBUG_OUT<<" name="<<a.name;
    DEBUG_OUT<<" '"<<tempString<<"'\n";
    newOffset+=readNameStringConstAtIndex(tempString,theNameIndex);
    DEBUG_OUT<<"Creating symbol...\n";
    anAttribute->setNum(t);
    theClass->attributes.append((void *)anAttribute);
    if(mySymtab) {
      AList_alib *symbols=mySymtab->getSymList();
      if(symbols) symbols->append((void *)anAttribute);
    }
    theCurrentOffset+=6;
    theCurrentOffset+=anAttribute->getSize();
    t++;
    if(t>theClass->numAttributes) reading=false;
  }
  return true;
}


// TODO: Move this to NJavaMethod class since it needs to access private members?
UINT NJavaClassDecoder::readConstantAtOffset(BSymbol *aSymbol,BOFF_T offset)
{
#ifdef DEBUG_VERBOSE
  //DEBUG_OUT<<"readConstantAtOffset(aSymbol,"<<offset<<")...\n";
#endif
  if(!aSymbol) { CONS_OUT<<"readConstantAtOffset() no aSymbol!\n"; return 0; }
  UINT total=0;
  //
  aSymbol->setAddress(offset);
  UINT javaSymbolType=memBlock->read8(offset);  offset+=1;
  aSymbol->setSymType(transJavaSymType(javaSymbolType));
  aSymbol->setSymbolName("in readConstantAtOffset()");  // Is this really necessary?!?
  aSymbol->setSize(0);
  aSymbol->setVal1(0);
  aSymbol->setVal2(0);
  aSymbol->setVal3(0);
  switch(aSymbol->getSymType()) {
    case ESYM_JVM_UTF8:
      aSymbol->setSize(memBlock->read16b(offset));  offset+=2;
      aSymbol->setVal1(offset); offset+=aSymbol->getSize();
      break;
    case ESYM_JVM_INT:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=4;
      break;
    case ESYM_JVM_FLOAT:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=4;
      break;
    case ESYM_JVM_LONG:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=4;
      aSymbol->setVal2(memBlock->read16b(offset));  offset+=4;
      break;
    case ESYM_JVM_DOUBLE:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=4;
      aSymbol->setVal2(memBlock->read16b(offset));  offset+=4;
      break;
    case ESYM_JVM_CLASS:
      aSymbol->setVal3(memBlock->read16b(offset));  offset+=2;
      break;
    case ESYM_JVM_STRING:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=2;
      break;
    case ESYM_JVM_FIELD:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=2;
      aSymbol->setVal2(memBlock->read16b(offset));  offset+=2;
      break;
    case ESYM_JVM_METHOD:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=2;
      aSymbol->setVal2(memBlock->read16b(offset));  offset+=2;
      break;
    case ESYM_JVM_INTERFACE:
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=2;
      aSymbol->setVal2(memBlock->read16b(offset));  offset+=2;
      break;
    case ESYM_JVM_NAMETYPE:
      aSymbol->setVal3(memBlock->read16b(offset));  offset+=2;
      aSymbol->setVal1(memBlock->read16b(offset));  offset+=2;
      break;
    default:
      CONS_OUT<<"readConstantAtOffset(aSymbol,"<<offset<<"): Bad constant type="<<aSymbol->getSymType()<<"!\n";
      //exit(EXIT_FAILURE);
      break;
  }
  total=offset-aSymbol->getAddress();
  return total;
}


// TODO: Move this to NJavaInterface class since it needs to access private members!
UINT NJavaClassDecoder::readInterfaceAtOffset(BSymbol *aSymbol,BOFF_T offset)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readInterfaceAtOffset(aSymbol,"<<offset<<")...\n";
#endif
  if(!aSymbol) { CONS_OUT<<"readInterfaceAtOffset() no aSymbol!\n"; return 0; }
  UINT total=0;
  // TODO
  return total;
}


// TODO: Move this to NJavaField class since it needs to access private members!
UINT NJavaClassDecoder::readFieldAtOffset(BSymbol *aSymbol,BOFF_T offset)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readFieldAtOffset(aSymbol,"<<offset<<")...\n";
#endif
  if(!aSymbol) { CONS_OUT<<"readFieldAtOffset() no aSymbol!\n"; return 0; }
  UINT total=0;
  // TODO
  return total;
}


// TODO: Move this to NJavaMethod class since it needs to access private members!
UINT NJavaClassDecoder::readMethodAtOffset(BSymbol *aSymbol,BOFF_T offset)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readMethodAtOffset(aSymbol,"<<offset<<")...\n";
#endif
  if(!aSymbol) { CONS_OUT<<"readMethodAtOffset() no aSymbol!\n"; return 0; }
  UINT total=0;
  //
  /*
  aMethod->addr=offset;
  aMethod->flags=memBlock->read16b(offset);  offset+=2;
  aMethod->nameIndex=memBlock->read16b(offset);  offset+=2;
  // 0x001=public 0x002=private 0x005=protected 0x008=static 0x010=final
  // 0x020=synchronized 0x100=native 0x400=abstract 0x800=strict
  aMethod->desc=memBlock->read16b(offset);  offset+=2;
  aMethod->numAttributes=memBlock->read16b(offset);  offset+=2;
  aMethod->attributes=offset;
  total=offset-aMethod->getAddress();  // NOTE: Not right, doesn't include attributes
  return total;
  */
  return total;
}


// TODO: Move this to NJavaAttribute class since it needs to access private members!
UINT NJavaClassDecoder::readAttributeAtOffset(BSymbol *aSymbol,BOFF_T offset)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readAttributeAtOffset(aSymbol,"<<offset<<")...\n";
#endif
  if(!aSymbol) { CONS_OUT<<"readAttributeAtOffset() no aSymbol!\n"; return 0; }
  UINT total=0;
  /*
  ULONG addr=0;
  UINT nameIndex=memBlock->read16b(offset);  offset+=2;
  ULONG len=memBlock->read32b(offset);  offset+=4;
  ULONG data=offset;
  NJavaAttribute *anAttribute=new NJavaAttribute(addr,nameIndex,len,data);
  return anAttribute;
  */
  return total;
}


// TODO: Move this to NJavaCode class since it needs to access private members!
UINT NJavaClassDecoder::readCodeAtOffset(BSymbol *aSymbol,BOFF_T offset)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readCodeAtOffset(aSymbol,"<<offset<<")...\n";
#endif
  if(!aSymbol) { CONS_OUT<<"readCodeAtOffset() no aSymbol!\n"; return 0; }
  UINT total=0;
  /*
  aCode->setAddress(offset);
  aCode->nameIndex=memBlock->read16b(offset); offset+=2;
  aCode->len=memBlock->read32b(offset); offset+=4;
  aCode->stackMax=memBlock->read16b(offset); offset+=2;
  aCode->localsMax=memBlock->read16b(offset); offset+=2;
  aCode->codeLen=memBlock->read32b(offset); offset+=4;
  aCode->codeAddr=offset;  offset+=aCode->codeLen;
  aCode->exceptionLen=memBlock->read16b(offset); offset+=2;
  aCode->exceptionAddr=offset;  offset+=aCode->exceptionLen;
  aCode->numAttrib=memBlock->read16b(offset); offset+=2;
  aCode->attribAddr=offset;
  total=offset-aCode->getAddress();  // NOTE: Not correct, doesn't include attribs
  return total;
  */
  return total;
}


UINT NJavaClassDecoder::readUTF8ConstAtIndex(char *aString,BOFF_T index)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"readUTF8ConstAtOffset(aString,"<<index<<")...\n";
#endif
  if(!aString) { CONS_OUT<<"NJavaClassDecoder::readUTF8ConstAtOffset() no aString!\n"; return 0; }
  aString[0]=0;
  if(!index) { aString[0]=0;  return 0; } //there is no const 0
  if(!(index<theClass->getNumConstants())) { /*DEBUG_OUT<<"(No contant "<<index<<" yet!)";*/  return 0; }
  UINT t=1;
  bool reading=true;
  while(reading) {
    if(t==index) {
      reading=false;
      //DEBUG_OUT<<"getTmpZeroStrAtOffset("<<theClass->constants[t].getLen()<<","<<theClass->constants[t].getNameIndex()<<")...\n";
      NJavaConstant *theConst=theClass->lookupConstant(t);
      if(theConst) getTmpZeroStrAtOffset(theConst->getNameIndex(),theConst->getSize());
      strcpy(aString,tempString);
      if(theConst) return theConst->getSize();
      else return 0;
    }
    else {
      t++;
      if(!(t<theClass->numConstants)) reading=false;
    }
  }
  return 0;
}


UINT NJavaClassDecoder::readNameStringConstAtIndex(char *aString,BOFF_T index)
{
#ifdef DEBUG_VERBOSE
  //DEBUG_OUT<<"readNameStringConstAtIndex(aString,"<<index<<")...\n";
#endif
  if(!aString) { CONS_OUT<<"NJavaClassDecoder::readNameStringConstAtIndex() no aString!\n"; return 0; }
  aString[0]=0;
  if(!index) { aString[0]=0;  return 0; } //there is no const 0
  if(!(index<theClass->getNumConstants())) { DEBUG_OUT<<"(too high)";  return 0; }
  aString[0]=0;
  UINT t=1;
  bool reading=true;
  while(reading) {
    if(t==index) {
      reading=false;
      //DEBUG_OUT<<"getTmpZeroStrAtOffset("<<theClass->constants[t].getLen()<<","<<theClass->constants[t].getNameIndex()<<")...\n";
      if(theClass) {
        NJavaConstant *theConst=theClass->lookupConstant(t);
        if(theConst) getTmpZeroStrAtOffset(theConst->getNameIndex(),theConst->getSize());
        else { DEBUG_OUT<<" NULL "; return 0; }
      }
      else { DEBUG_OUT<<"theClass was NULL!\n"; exit(EXIT_FAILURE); }
      strcpy(aString,tempString);
      NJavaConstant *theConst=theClass->lookupConstant(t);
      if(theConst) return theConst->getSize();
      else { DEBUG_OUT<<" NULL "; return 0; }
    }
    else {
      t++;
      if(!(t<theClass->numConstants)) reading=false;
    }
  }
  return 0;
}


BClassObject *NJavaClassDecoder::getTheClassObject()
{
  return theClass;
}


// This translates small number actual java type codes to avoid collision with ELF ones
UINT NJavaClassDecoder::transJavaSymType(UINT javaType)
{
  UINT ret=0;
  switch(javaType) {
    case NJCD_TYPE_CLASS: ret=ESYM_JVM_CLASS; break;
    case NJCD_TYPE_FIELDREF: ret=ESYM_JVM_FIELD; break;
    case NJCD_TYPE_METHODREF: ret=ESYM_JVM_METHOD; break;
    case NJCD_TYPE_INTERFACEMETHODREF: ret=ESYM_JVM_INTERFACE; break;
    case NJCD_TYPE_STRING: ret=ESYM_JVM_STRING; break;
    case NJCD_TYPE_INTEGER: ret=ESYM_JVM_INT; break;
    case NJCD_TYPE_FLOAT: ret=ESYM_JVM_FLOAT; break;
    case NJCD_TYPE_LONG: ret=ESYM_JVM_LONG; break;
    case NJCD_TYPE_DOUBLE: ret=ESYM_JVM_DOUBLE; break;
    case NJCD_TYPE_NAMEANDTYPE: ret=ESYM_JVM_NAMETYPE; break;
    case NJCD_TYPE_UTF8: ret=ESYM_JVM_UTF8; break;
    case NJCD_TYPE_METHODHANDLE: ret=ESYM_JVM_METHODHAND; break;
    case NJCD_TYPE_METHODTYPE: ret=ESYM_JVM_METHOD_ATTR; break;
    case NJCD_TYPE_INVOKEDYNAMIC: ret=ESYM_JVM_INVOKEDYNAMIC; break;
    default:
      // Shouldn't happen!
      ret=0;
      break;
  }
  return ret;
}


void NJavaClassDecoder::debugDump()
{
  DEBUG_OUT<<"NJavaClassDecoder...\n";
  BBinaryDecoder::debugDump();
}


#endif
