#ifndef BINARYLIB_NJAVACLASSDECODER_H
#define BINARYLIB_NJAVACLASSDECODER_H


#include "../../cpp/alib/abaseclass.h"

#include "../../nemu/binarylib/BBinaryDecoder.h"
#include "../../nemu/binarylib/BClassObject.h"

#include "../../nemu/elib/EMapAbstract.h"


#ifdef NEMU_INCLUDE_JAVA


#include "classparts/NJavaClass.h"
#include "classparts/NJavaInterface.h"
#include "classparts/NJavaField.h"
#include "classparts/NJavaMethod.h"
#include "classparts/NJavaAttribute.h"
#include "classparts/NJavaCode.h"


// NOTE: These are not dups of the ones in BBinaryTypes.h
// They are the actual values you find in the .class file

// Extra Java specific symbol types...
// I made these up
#define NJAVA_SYM_CONSTANT 1024
#define NJAVA_SYM_INTERFACE 1025
#define NJAVA_SYM_FIELD 1026
#define NJAVA_SYM_METHOD 1027
#define NJAVA_SYM_METHOD_ATTRIBUTE 1028
#define NJAVA_SYM_ATTRIBUTE 1029
#define NJAVA_SYM_CODE 1030


#define NJCD_TYPE_CLASS 7
#define NJCD_TYPE_FIELDREF 9
#define NJCD_TYPE_METHODREF 10
#define NJCD_TYPE_INTERFACEMETHODREF 11
#define NJCD_TYPE_STRING 8
#define NJCD_TYPE_INTEGER 3
#define NJCD_TYPE_FLOAT 4
#define NJCD_TYPE_LONG 5
#define NJCD_TYPE_DOUBLE 6
#define NJCD_TYPE_NAMEANDTYPE 12
#define NJCD_TYPE_UTF8 1
#define NJCD_TYPE_METHODHANDLE 15
#define NJCD_TYPE_METHODTYPE 16
#define NJCD_TYPE_INVOKEDYNAMIC 18


class NJavaClassDecoder : public BBinaryDecoder
{
public:
  NJavaClassDecoder(const char *fname);
  virtual ~NJavaClassDecoder();
  //
  virtual void debugDump();
  //
  static bool recognize(unsigned char *buf,const char *fname=(char *)NULL);
  virtual const char *whichCPUName();
  virtual const char *whichIOType();
  virtual bool verifyOkay();
  virtual const char *getName() { return (char *)"NJavaClassDecoder"; }
  virtual bool decodeBinary();
  //
  virtual BClassObject *getTheClassObject();
  //
protected:
  //
  virtual void init();
  // these return the full size of the object (including trailing data, etc). 0=didn't work
  virtual UINT readConstantAtOffset(BSymbol *aSymbol,BOFF_T offset);
  virtual UINT readInterfaceAtOffset(BSymbol *aSymbol,BOFF_T offset);
  virtual UINT readFieldAtOffset(BSymbol *aSymbol,BOFF_T offset);
  virtual UINT readMethodAtOffset(BSymbol *aSymbol,BOFF_T offset);
  virtual UINT readAttributeAtOffset(BSymbol *aSymbol,BOFF_T offset);
  //
  virtual UINT readCodeAtOffset(BSymbol *aSymbol,BOFF_T offset);
  //
  virtual UINT readNameStringConstAtIndex(char *aString,BOFF_T offset);
  virtual UINT readUTF8ConstAtIndex(char *aString,BOFF_T offset);
  //
  // misc helper methods
  virtual bool readConstants(UINT numConsts);
  void fixContantNames();
  void goBackAndFixMoreNames();
  virtual bool decodeInterfaces();
  virtual bool decodeFields();
  virtual bool decodeMethods();
  virtual bool decodeAttributes();
  //
  UINT transJavaSymType(UINT javaType);
  //
  // Private Data Members
  //
  NJavaClass *theClass;
};


#endif


#endif
