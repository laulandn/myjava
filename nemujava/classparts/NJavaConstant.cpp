
#define ERR_OUT std::cerr
#define CONS_OUT std::cout
#define CONS_IN std::cin
#define DEBUG_OUT dBug


#include "../../../cpp/alib/adebug.h"
#include "../../../../more_src/nlib/nlibdbug.h"

#include "NJavaConstant.h"


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif


////////////////////////////////////////////////////////////////////////////////
//  NJavaConstant Class
////////////////////////////////////////////////////////////////////////////////


NJavaConstant::NJavaConstant()
{
  DEBUG_OUT<<"NJavaConstant::NJavaConstant()\n";
  init();
  addr=0;
  nameIndex=0;
  theSize=0;
}


NJavaConstant::~NJavaConstant()
{
}


void NJavaConstant::init()
{
  addr=0;
  theSize=0;
  nameIndex=0;
  otherIndex=0;
  typeIndex=0;
  theName=NULL;
  theOther=NULL;
  theType=NULL;
}


const char *NJavaConstant::lookupString()
{
  return NULL;
}


void NJavaConstant::debugDump()
{
  //DEBUG_OUT<<"NJavaConstant: "<<ALIB2HEX8(addr)<<","<<nameIndex<<","<<len<<","<<data<<"\n";
  char *tempString=(char *)"";
  /*
    switch(getType()) {
      case ESYM_JVM_UTF8:
        DEBUG_OUT<<"Utf8 ";
        //DEBUG_OUT<<getName();
        break;
      case ESYM_JVM_INT:
        DEBUG_OUT<<"Int ";
        break;
      case ESYM_JVM_FLOAT:
        DEBUG_OUT<<"Float ";
        break;
      case ESYM_JVM_LONG:
        DEBUG_OUT<<"Long ";
        break;
      case ESYM_JVM_DOUBLE:
        DEBUG_OUT<<"Double ";
        break;
      case ESYM_JVM_CLASS:
        DEBUG_OUT<<"Class ";
        //DEBUG_OUT<<"  #"<<getVal3();
        //DEBUG_OUT<<"  // "<<getName();
        break;
      case ESYM_JVM_STRING:
        DEBUG_OUT<<"String ";
        //DEBUG_OUT<<"  #"<<getVal1();
        //DEBUG_OUT<<"  // "<<getName();
        break;
      case ESYM_JVM_FIELD:
        DEBUG_OUT<<"Fieldref ";
        //DEBUG_OUT<<"  #"<<getVal1()<<".#"<<getVal2();
        //DEBUG_OUT<<"  // "<<getName();
        // DEBUG_OUT<<" "; printNameType(getVal2());
       break;
      case ESYM_JVM_METHOD:
        DEBUG_OUT<<"Methodref ";
        //DEBUG_OUT<<"  #"<<getVal1()<<".#"<<getVal2();
        //DEBUG_OUT<<"  // "<<getName();
        //DEBUG_OUT<<" "; printNameType(getVal2());
        break;
      case ESYM_JVM_INTERFACE:
        DEBUG_OUT<<"Interfaceref ";
        //DEBUG_OUT<<"  #"<<getVal1()<<".#"<<getVal2();
        //DEBUG_OUT<<"  // "<<getName();
        //DEBUG_OUT<<" "; printNameType(getVal2());
        break;
      case ESYM_JVM_NAMETYPE:
        DEBUG_OUT<<"NameAndType ";
        //DEBUG_OUT<<"  #"<<getVal3()<<".#"<<getVal1();
        //DEBUG_OUT<<"  // "; printNameType(getNum());
        break;
      default:
        DEBUG_OUT<<"bad constant type!";
        exit(EXIT_FAILURE);
        break;
    }
    DEBUG_OUT<<"\n";
*/
}
