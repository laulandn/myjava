
#define DEBUG_OUT dBug
#define ERR_OUT std::cerr
//#define DEBUG_OUT *debugOut
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cout
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream


#ifdef NEMU_INCLUDE_JAVA


#define DEBUG_DIS_MODES 1
#define DEBUG_EXEC 1
#define CHECK_SAFE 1
#define CHECK_STACK  1
//#define SHOW_INTS  1
//#define USE_FANCY_REG_NAMES 1
//#define USE_NONSTANDARD_ASM 1


#include "EJavaBytecode.h"

#include "EJVM_tab.h"

#include "../../nemu/binarylib/BSymbolTable.h"

#include "../../cpp/alib/adebug.h"
#include "../../cpp/alib/abasics.h"



//#include "../NJLoaderLib/NJavaClassDecoder.h"


// The different cpus...
#define E_CPU_NONE     0x00
#define E_CPU_JVM      0x01
#define E_CPU_JS       0x02


////////////////////////////////////////////////////////////////////////////////
//  EJavaBytecode Class
////////////////////////////////////////////////////////////////////////////////

EJavaBytecode::EJavaBytecode(EMapAbstract *aMap)
{
  DEBUG_OUT<<"EJavaBytecode created...\n";
  init();
  type=E_CPU_JVM;
  //w=ww;
  resetCpu();
  myMap=aMap;
}


EJavaBytecode::~EJavaBytecode()
{
  CONS_OUT<<"EJavaBytecode::~EJavaBytecode()\n";
}


void EJavaBytecode::init()
{
  EBytecodeCPU::init();
  setBitness(32);
  setLittleEndian(false);  // hmm?
  // Generic features
  doTrace=false;  doRun=false;
  // Set up stack and registers
  int_pending=0;
  intLock=false;
  setStack(ECPU_DEFAULT_STACK);
  setFramePtr(ECPU_DEFAULT_STACK);
  setResetStack(ECPU_DEFAULT_STACK);
}


bool EJavaBytecode::recognizeName(const char *tname)
{
  const char *name=DSHELPER_alib.removeSpaces2(DSHELPER_alib.toLower(tname));
  if(!strcmp(name,"jvm")) return true;
  if(!strcmp(name,"java")) return true;
  if(!strcmp(name,"javabytecode")) return true;
  return false;
}


const char *EJavaBytecode::getName()
{
  return "Java JVM";
}


void EJavaBytecode::setKind(const char *tname)
{
  //const char *name=DSHELPER_alib.removeSpaces2(DSHELPER_alib.toLower(tname));
  type=E_CPU_JVM;
}


void EJavaBytecode::resetCpu()
{
  //ERR_OUT<<"EJavaBytecode::resetCpu().\n";
#ifdef DEBUG_EXEC
  setTrace(true);
#endif
  intLock=false;
  pc=0;  // Jump to zero
  if(resetStack) { setStack(resetStack); setFramePtr(resetStack); }
  clearStackTrace();
  EBytecodeObject o;
  // array of command line args...none for now
  o.type=ECPU_TYPE_ARRAY;
  o.len=0;
  o.val=0;
  o.name=0;
  pushObj(&o);
  if(resetEntryPoint!=ECPU_DEFAULT_CODE) { jump(resetEntryPoint); } else { DEBUG_OUT<<"resetEntryPoint is still ECPU_DEFAULT_CODE!\n"; }
}


bool EJavaBytecode::setRegister(const char *tname,EOPSIZE_T value)
{
  const char *name=DSHELPER_alib.removeSpaces2(DSHELPER_alib.toLower(tname));
  bool ret=false;
  if(!strcmp(name,"pc"))
  { pc=value; ret=true; } else
  if(!strcmp(name,"sp"))
  { sp=value; ret=true; }
  //free(name);
  return ret;
}


EOPSIZE_T EJavaBytecode::readRegister(const char *name)
{
  if(!strcmp(name,"sp")) { return sp; }
  return 0;
}


void EJavaBytecode::wregs()
{
  CONS_OUT<<"PC="<<ALIB2HEX8(pc)<<"\n";
  CONS_OUT<<"SP="<<ALIB2HEX8(sp)<<"\n";
}


void EJavaBytecode::handle_int(EADDR_T value)
{
}


void EJavaBytecode::cause_int(EADDR_T value)
{
  int_pending=0;
  switch(value) {
    default:
      cpuDebugger(ECPU_ERR_ILLEGALINT);
      break;
  }
}


void EJavaBytecode::ints()
{
  //if(w) {
  //}
}


void EJavaBytecode::execute()
{
  //if(!lastUsedAddress) loadInitialClass();
  checkIfBreakpoint(pc);
  theOpcode=myMap->read8(pc);
  instLen=EJVM_size[theOpcode];
  instCycles=EJVM_time[theOpcode];
  UINT loc=pc;
#include "EJVM_exec.h"
  pc+=instLen;
  cycles+=instCycles;
  if(int_pending) handle_int(int_pending);
}


EADDR_T EJavaBytecode::disasm(EADDR_T loc)
{
  uint8_t tOpcode;
  UINT mode=EJVM_ADDR_NONE;
  const char *name="???";
  tOpcode=myMap->read8(loc);
  lastSymbol=myMap->getSymtab()->lookupExactSymByAddr(loc);
  if(lastSymbol) CONS_OUT<<lastSymbol->getSymbolName()<<":\n";
  CONS_OUT<<"."; CONS_OUT<<ALIB2HEX8(loc);  CONS_OUT<<"  ";
  instLen=EJVM_size[tOpcode];
  mode=EJVM_format[tOpcode];
  name=EJVM_name[tOpcode];
  if(!instLen) instLen=1;  // NOTE: An unimplemented opcode...
  UINT t;
  for(t=0;t<instLen;t++) CONS_OUT<<ALIB2HEX2NX(myMap->read8(loc+t))<<" ";
  for(t=0;t<(3-instLen);t++) CONS_OUT<<"   ";
  CONS_OUT<<" "<<name<<" ";
  //DEBUG_OUT<<"Len was "<<len<<"\n";
  instLen+=printAddrMode(loc,tOpcode,mode);
  //DEBUG_OUT<<"Len now is "<<len<<"\n";
  CONS_OUT<<"\n";
  return instLen;
}


UINT EJavaBytecode::printAddrMode(EADDR_T loc,EOPSIZE_T tOpcode,UINT mode)
{
  switch(mode) {
    case EJVM_ADDR_NONE:
      break;
    case EJVM_ADDR_ONE:
      break;
    case EJVM_ADDR_TWO:
      break;
    case EJVM_ADDR_IMM8:
      CONS_OUT<<myMap->read8(loc+1);
      break;
    case EJVM_ADDR_IMM16:
      CONS_OUT<<myMap->read16b(loc+1);
      break;
    default:
      cpuDebugger("Bad addr mode!\n");
      break;
  }
  return 0;
}


void EJavaBytecode::invoke_helper(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT type=0,num=0,name=0;
  EADDR_T addr=0;
  num=myMap->read16b(loc+1);
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(num);
  if(!sym) {
    cpuDebugger("invoke_helper didn't find needed constant!\n");
    return;
  }
  DEBUG_OUT<<"invoke_helper num="<<num<<" type="<<sym->getSymType()<<"\n";
  if(sym->getSymType()==ECPU_TYPE_METHODREF) {
    type=sym->getVal1();
    name=sym->getVal2();
    /*
    UINT numArgs=2;  // TODO: read method sig for this...
    EBytecodeObject *args[10];
    UINT t=0;
    for(t=0;t<10;t++) args[t]=NULL;
    for(t=0;t<numArgs;t++) {
      args[t]=popObj();
    }
    */
    CONS_OUT<<"invoke_helper["<<"type="<<type<<" name="<<name<<"] #"<<num<<"\n";
    CONS_OUT<<"method='"<<sym->getSymbolName()<<"'\n";
    s[0]=0;
    getNameString(s,type);
    CONS_OUT<<"class='"<<s<<"'\n";
    s[0]=0;
    getNameString(s,name);
    CONS_OUT<<"signature='"<<s<<"'\n";
    BSymbol *sym2=myMap->getSymtab()->lookupSymByName(s);
    if(sym2) addr=sym2->getAddress();
    if(addr) {
      jump(addr);
    }
    else {
      cpuDebugger("Couldn't locate method to jump to!");
    }
  }
  else {
    cpuDebugger("Bad invoke_helper constant type!");
  }
}


void EJavaBytecode::aload_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"aload #"<<num<<" (array)\n";
  cpuDebugger("Unimplemented aload_helper");
}


void EJavaBytecode::iload_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"iload #"<<num<<" (int)\n";
  cpuDebugger("Unimplemented iload_helper");
}


void EJavaBytecode::lload_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"lload #"<<num<<" (long)\n";
  cpuDebugger("Unimplemented lload_helper");
}


void EJavaBytecode::fload_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"fload #"<<num<<" (float)\n";
  cpuDebugger("Unimplemented fload_helper");
}


void EJavaBytecode::dload_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"dload #"<<num<<" (double)\n";
  cpuDebugger("Unimplemented dload_helper");
}


void EJavaBytecode::astore_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"astore #"<<num<<" (double)\n";
  cpuDebugger("Unimplemented dload_helper");
}


void EJavaBytecode::istore_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"istore #"<<num<<" (double)\n";
  cpuDebugger("Unimplemented dload_helper");
}


void EJavaBytecode::lstore_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"lstore #"<<num<<" (double)\n";
  cpuDebugger("Unimplemented dload_helper");
}


void EJavaBytecode::fstore_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"fstore #"<<num<<" (double)\n";
  cpuDebugger("Unimplemented dload_helper");
}


void EJavaBytecode::dstore_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  DEBUG_OUT<<"dstore #"<<num<<" (double)\n";
  cpuDebugger("Unimplemented dload_helper");
}


void EJavaBytecode::iconst_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  EBytecodeObject o;
  o.type=ECPU_TYPE_INTEGER;
  o.val=num;
  o.name=0;
  o.len=0;
  pushObj(&o);
  DEBUG_OUT<<"iconst #"<<o.val<<" (int)\n";
}


void EJavaBytecode::lconst_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  EBytecodeObject o;
  o.type=ECPU_TYPE_LONG;
  o.val=num;
  o.name=0;
  o.len=0;
  pushObj(&o);
  DEBUG_OUT<<"lconst #"<<o.val<<" (long)\n";
}


// TODO: obviously this should be float not int
void EJavaBytecode::fconst_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  EBytecodeObject o;
  o.type=ECPU_TYPE_FLOAT;
  o.val=num;
  o.name=0;
  o.len=0;
  pushObj(&o);
  DEBUG_OUT<<"fconst #"<<o.val<<" (float)\n";
}


// TODO: obviously this should be float not int
void EJavaBytecode::dconst_helper(EADDR_T loc, EOPSIZE_T opcode, UINT num)
{
  EBytecodeObject o;
  o.type=ECPU_TYPE_DOUBLE;
  o.val=num;
  o.name=0;
  o.len=0;
  pushObj(&o);
  DEBUG_OUT<<"dconst #"<<o.val<<" (double)\n";
}


// copied from NJavaClassDecoder...for now
void EJavaBytecode::getStringAtAddr(char *s,ESIZE_T len,EADDR_T addr)
{
  if(!s) return;
  UINT i=0;
  for(i=0;i<len;i++) s[i]=myMap->read8(addr+i);
  s[i]=0;
}


UINT EJavaBytecode::getNameString(char *s,UINT index)
{
  if(!s) return 0;
  if(!index) { s[0]=0;  return 0; } //there is no const 0
  s[0]=0;
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(index);
  if(sym) {
    strcpy(s,sym->getSymbolName());
    return strlen(s);
  }
  return 0;
}


UINT EJavaBytecode::getNameStringVal(char *s,UINT index)
{
  if(!s) return 0;
  if(!index) { s[0]=0;  return 0; } //there is no const 0
  s[0]=0;
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(index);
  if(sym) {
    return getNameString(s,sym->getVal1());
  }
  return 0;
}


UINT EJavaBytecode::getNameStringVal2(char *s,UINT index)
{
  if(!s) return 0;
  if(!index) { s[0]=0;  return 0; } //there is no const 0
  s[0]=0;
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(index);
  if(sym) {
    return getNameString(s,sym->getVal2());
  }
  return 0;
}


UINT EJavaBytecode::getNameStringMisc(char *s,UINT index)
{
  if(!s) return 0;
  if(!index) { s[0]=0;  return 0; } //there is no const 0
  s[0]=0;
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(index);
  if(sym) {
    return getNameString(s,sym->getVal3());
  }
  return 0;
}


void EJavaBytecode::exec_nop(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented nop opcode");
}


void EJavaBytecode::exec_aconst_null(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented aconst_null opcode");
}


void EJavaBytecode::exec_iconst_m1(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iconst_m1 opcode");
}


void EJavaBytecode::exec_iconst_0(EADDR_T loc,EOPSIZE_T opcode)
{
  iconst_helper(loc,opcode,0);
}


void EJavaBytecode::exec_iconst_1(EADDR_T loc,EOPSIZE_T opcode)
{
  iconst_helper(loc,opcode,1);
}


void EJavaBytecode::exec_iconst_2(EADDR_T loc,EOPSIZE_T opcode)
{
  iconst_helper(loc,opcode,2);
}


void EJavaBytecode::exec_iconst_3(EADDR_T loc,EOPSIZE_T opcode)
{
  iconst_helper(loc,opcode,3);
}


void EJavaBytecode::exec_iconst_4(EADDR_T loc,EOPSIZE_T opcode)
{
  iconst_helper(loc,opcode,4);
}


void EJavaBytecode::exec_iconst_5(EADDR_T loc,EOPSIZE_T opcode)
{
  iconst_helper(loc,opcode,5);
}


void EJavaBytecode::exec_lconst_0(EADDR_T loc,EOPSIZE_T opcode)
{
  lconst_helper(loc,opcode,0);
}


void EJavaBytecode::exec_lconst_1(EADDR_T loc,EOPSIZE_T opcode)
{
  lconst_helper(loc,opcode,1);
}


void EJavaBytecode::exec_fconst_0(EADDR_T loc,EOPSIZE_T opcode)
{
  fconst_helper(loc,opcode,0);
}


void EJavaBytecode::exec_fconst_1(EADDR_T loc,EOPSIZE_T opcode)
{
  fconst_helper(loc,opcode,1);
}


void EJavaBytecode::exec_fconst_2(EADDR_T loc,EOPSIZE_T opcode)
{
  fconst_helper(loc,opcode,2);
}


void EJavaBytecode::exec_dconst_0(EADDR_T loc,EOPSIZE_T opcode)
{
  dconst_helper(loc,opcode,0);
}


void EJavaBytecode::exec_dconst_1(EADDR_T loc,EOPSIZE_T opcode)
{
  dconst_helper(loc,opcode,1);
}


void EJavaBytecode::exec_bipush(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented bipush opcode");
}


void EJavaBytecode::exec_sipush(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented sipush opcode");
}


void EJavaBytecode::exec_ldc(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  num=myMap->read8(loc+1);
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(num);
  if(!sym) {
    cpuDebugger("ldc didn't find needed constant!\n");
    return;
  }
  DEBUG_OUT<<"ldc num="<<num<<" type="<<sym->getSymType()<<"\n";
  if(sym->getSymType()==ECPU_TYPE_STRING) {
    EBytecodeObject o;
    o.type=0;
    o.val=sym->getVal1();
    o.name=0;
    o.len=0;
    pushObj(&o);
    DEBUG_OUT<<"ldc["<<o.val<<"] ";
    s[0]=0;
    getNameString(s,o.val); // value?
    DEBUG_OUT<<s<<"\n";
  }
  else {
    cpuDebugger("Bad ldc constant type!");
  }
}


void EJavaBytecode::exec_ldc_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ldc_w opcode");
}


void EJavaBytecode::exec_ldc2_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ldc2_w opcode");
}


void EJavaBytecode::exec_iload(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 16 or 32 bits?
  iload_helper(loc,opcode,num);
}


void EJavaBytecode::exec_lload(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 16 or 32 bits?
  lload_helper(loc,opcode,num);
}


void EJavaBytecode::exec_fload(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 32 or 64 bits?
  fload_helper(loc,opcode,num);
}


void EJavaBytecode::exec_dload(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 32 or 64 bits?
  dload_helper(loc,opcode,num);
}


void EJavaBytecode::exec_aload(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, array?!?
  aload_helper(loc,opcode,num);
}


void EJavaBytecode::exec_iload_0(EADDR_T loc,EOPSIZE_T opcode)
{
  iload_helper(loc,opcode,0);
}


void EJavaBytecode::exec_iload_1(EADDR_T loc,EOPSIZE_T opcode)
{
  iload_helper(loc,opcode,1);
}


void EJavaBytecode::exec_iload_2(EADDR_T loc,EOPSIZE_T opcode)
{
  iload_helper(loc,opcode,2);
}


void EJavaBytecode::exec_iload_3(EADDR_T loc,EOPSIZE_T opcode)
{
  iload_helper(loc,opcode,3);
}


void EJavaBytecode::exec_lload_0(EADDR_T loc,EOPSIZE_T opcode)
{
  lload_helper(loc,opcode,0);
}


void EJavaBytecode::exec_lload_1(EADDR_T loc,EOPSIZE_T opcode)
{
  lload_helper(loc,opcode,1);
}


void EJavaBytecode::exec_lload_2(EADDR_T loc,EOPSIZE_T opcode)
{
  lload_helper(loc,opcode,2);
}


void EJavaBytecode::exec_lload_3(EADDR_T loc,EOPSIZE_T opcode)
{
  lload_helper(loc,opcode,3);
}


void EJavaBytecode::exec_fload_0(EADDR_T loc,EOPSIZE_T opcode)
{
  fload_helper(loc,opcode,0);
}


void EJavaBytecode::exec_fload_1(EADDR_T loc,EOPSIZE_T opcode)
{
  fload_helper(loc,opcode,1);
}


void EJavaBytecode::exec_fload_2(EADDR_T loc,EOPSIZE_T opcode)
{
  fload_helper(loc,opcode,2);
}


void EJavaBytecode::exec_fload_3(EADDR_T loc,EOPSIZE_T opcode)
{
  fload_helper(loc,opcode,3);
}


void EJavaBytecode::exec_dload_0(EADDR_T loc,EOPSIZE_T opcode)
{
  dload_helper(loc,opcode,0);
}


void EJavaBytecode::exec_dload_1(EADDR_T loc,EOPSIZE_T opcode)
{
  dload_helper(loc,opcode,1);
}


void EJavaBytecode::exec_dload_2(EADDR_T loc,EOPSIZE_T opcode)
{
  dload_helper(loc,opcode,2);
}


void EJavaBytecode::exec_dload_3(EADDR_T loc,EOPSIZE_T opcode)
{
  dload_helper(loc,opcode,3);
}


void EJavaBytecode::exec_aload_0(EADDR_T loc,EOPSIZE_T opcode)
{
  aload_helper(loc,opcode,0);
}


void EJavaBytecode::exec_aload_1(EADDR_T loc,EOPSIZE_T opcode)
{
  aload_helper(loc,opcode,1);
}


void EJavaBytecode::exec_aload_2(EADDR_T loc,EOPSIZE_T opcode)
{
  aload_helper(loc,opcode,2);
}


void EJavaBytecode::exec_aload_3(EADDR_T loc,EOPSIZE_T opcode)
{
  aload_helper(loc,opcode,3);
}


void EJavaBytecode::exec_iaload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iaload opcode");
}


void EJavaBytecode::exec_laload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented laload opcode");
}


void EJavaBytecode::exec_faload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented faload opcode");
}


void EJavaBytecode::exec_daload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented daload opcode");
}


void EJavaBytecode::exec_aaload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented aaload opcode");
}


void EJavaBytecode::exec_baload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented baload opcode");
}


void EJavaBytecode::exec_caload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented caload opcode");
}


void EJavaBytecode::exec_saload(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented saload opcode");
}


void EJavaBytecode::exec_istore(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 16 or 32 bits?
  istore_helper(loc,opcode,num);
}


void EJavaBytecode::exec_lstore(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 32 bits?
  lstore_helper(loc,opcode,num);
}


void EJavaBytecode::exec_fstore(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 32 or 64 bits?
  fstore_helper(loc,opcode,num);
}


void EJavaBytecode::exec_dstore(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, 32 or 64 bits?
  dstore_helper(loc,opcode,num);
}


void EJavaBytecode::exec_astore(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  // TODO: get num, array?!?
  astore_helper(loc,opcode,num);
}


void EJavaBytecode::exec_istore_0(EADDR_T loc,EOPSIZE_T opcode)
{
  istore_helper(loc,opcode,0);
}


void EJavaBytecode::exec_istore_1(EADDR_T loc,EOPSIZE_T opcode)
{
  istore_helper(loc,opcode,1);
}


void EJavaBytecode::exec_istore_2(EADDR_T loc,EOPSIZE_T opcode)
{
  istore_helper(loc,opcode,2);
}


void EJavaBytecode::exec_istore_3(EADDR_T loc,EOPSIZE_T opcode)
{
  istore_helper(loc,opcode,3);
}


void EJavaBytecode::exec_lstore_0(EADDR_T loc,EOPSIZE_T opcode)
{
  lstore_helper(loc,opcode,0);
}


void EJavaBytecode::exec_lstore_1(EADDR_T loc,EOPSIZE_T opcode)
{
  lstore_helper(loc,opcode,1);
}


void EJavaBytecode::exec_lstore_2(EADDR_T loc,EOPSIZE_T opcode)
{
  lstore_helper(loc,opcode,2);
}


void EJavaBytecode::exec_lstore_3(EADDR_T loc,EOPSIZE_T opcode)
{
  lstore_helper(loc,opcode,3);
}


void EJavaBytecode::exec_fstore_0(EADDR_T loc,EOPSIZE_T opcode)
{
  fstore_helper(loc,opcode,0);
}


void EJavaBytecode::exec_fstore_1(EADDR_T loc,EOPSIZE_T opcode)
{
  fstore_helper(loc,opcode,1);
}


void EJavaBytecode::exec_fstore_2(EADDR_T loc,EOPSIZE_T opcode)
{
  fstore_helper(loc,opcode,2);
}


void EJavaBytecode::exec_fstore_3(EADDR_T loc,EOPSIZE_T opcode)
{
  fstore_helper(loc,opcode,3);
}


void EJavaBytecode::exec_dstore_0(EADDR_T loc,EOPSIZE_T opcode)
{
  dstore_helper(loc,opcode,0);
}


void EJavaBytecode::exec_dstore_1(EADDR_T loc,EOPSIZE_T opcode)
{
  dstore_helper(loc,opcode,1);
}


void EJavaBytecode::exec_dstore_2(EADDR_T loc,EOPSIZE_T opcode)
{
  dstore_helper(loc,opcode,2);
}


void EJavaBytecode::exec_dstore_3(EADDR_T loc,EOPSIZE_T opcode)
{
  dstore_helper(loc,opcode,3);
}


void EJavaBytecode::exec_astore_0(EADDR_T loc,EOPSIZE_T opcode)
{
  astore_helper(loc,opcode,0);
}


void EJavaBytecode::exec_astore_1(EADDR_T loc,EOPSIZE_T opcode)
{
  astore_helper(loc,opcode,1);
}


void EJavaBytecode::exec_astore_2(EADDR_T loc,EOPSIZE_T opcode)
{
  astore_helper(loc,opcode,2);
}


void EJavaBytecode::exec_astore_3(EADDR_T loc,EOPSIZE_T opcode)
{
  astore_helper(loc,opcode,3);
}


void EJavaBytecode::exec_iastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iastore opcode");
}


void EJavaBytecode::exec_lastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lastore opcode");
}


void EJavaBytecode::exec_fastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fastore opcode");
}


void EJavaBytecode::exec_dastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dastore opcode");
}


void EJavaBytecode::exec_aastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented aastore opcode");
}


void EJavaBytecode::exec_bastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented bastore opcode");
}


void EJavaBytecode::exec_castore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented castore opcode");
}


void EJavaBytecode::exec_sastore(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented sastore opcode");
}


void EJavaBytecode::exec_pop(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented pop opcode");
}


void EJavaBytecode::exec_pop2(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented pop2 opcode");
}


void EJavaBytecode::exec_dup(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dup opcode");
}


void EJavaBytecode::exec_dup_x1(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dup_x1 opcode");
}


void EJavaBytecode::exec_dup_x2(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dup_x2 opcode");
}


void EJavaBytecode::exec_dup2(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dup2 opcode");
}


void EJavaBytecode::exec_dup2_x1(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dup2_x1 opcode");
}


void EJavaBytecode::exec_dup2_x2(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dup2_x2 opcode");
}


void EJavaBytecode::exec_swap(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented swap opcode");
}


void EJavaBytecode::exec_iadd(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iadd opcode");
}


void EJavaBytecode::exec_ladd(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ladd opcode");
}


void EJavaBytecode::exec_fadd(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fadd opcode");
}


void EJavaBytecode::exec_dadd(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dadd opcode");
}


void EJavaBytecode::exec_isub(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented isub opcode");
}


void EJavaBytecode::exec_lsub(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lsub opcode");
}


void EJavaBytecode::exec_fsub(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fsub opcode");
}


void EJavaBytecode::exec_dsub(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dsub opcode");
}


void EJavaBytecode::exec_imul(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented imul opcode");
}


void EJavaBytecode::exec_lmul(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lmul opcode");
}


void EJavaBytecode::exec_fmul(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fmul opcode");
}


void EJavaBytecode::exec_dmul(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dmul opcode");
}


void EJavaBytecode::exec_idiv(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented idiv opcode");
}


void EJavaBytecode::exec_ldiv(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ldiv opcode");
}


void EJavaBytecode::exec_fdiv(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fdiv opcode");
}


void EJavaBytecode::exec_ddiv(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ddiv opcode");
}


void EJavaBytecode::exec_irem(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented irem opcode");
}


void EJavaBytecode::exec_lrem(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lrem opcode");
}


void EJavaBytecode::exec_frem(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented frem opcode");
}


void EJavaBytecode::exec_drem(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented drem opcode");
}


void EJavaBytecode::exec_ineg(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ineg opcode");
}


void EJavaBytecode::exec_lneg(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lneg opcode");
}


void EJavaBytecode::exec_fneg(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fneg opcode");
}


void EJavaBytecode::exec_dneg(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dneg opcode");
}


void EJavaBytecode::exec_ishl(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ishl opcode");
}


void EJavaBytecode::exec_lshl(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lshl opcode");
}


void EJavaBytecode::exec_ishr(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ishr opcode");
}


void EJavaBytecode::exec_lshr(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lshr opcode");
}


void EJavaBytecode::exec_iushr(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iushr opcode");
}


void EJavaBytecode::exec_lushr(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lushr opcode");
}


void EJavaBytecode::exec_iand(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iand opcode");
}


void EJavaBytecode::exec_land(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented land opcode");
}


void EJavaBytecode::exec_ior(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ior opcode");
}


void EJavaBytecode::exec_lor(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lor opcode");
}


void EJavaBytecode::exec_ixor(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ixor opcode");
}


void EJavaBytecode::exec_lxor(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lxor opcode");
}


void EJavaBytecode::exec_iinc(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iinc opcode");
}


void EJavaBytecode::exec_i2l(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented i2l opcode");
}


void EJavaBytecode::exec_i2f(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented i2f opcode");
}


void EJavaBytecode::exec_i2d(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented i2d opcode");
}


void EJavaBytecode::exec_l2i(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented l2i opcode");
}


void EJavaBytecode::exec_l2f(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented l2f opcode");
}


void EJavaBytecode::exec_l2d(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented l2d opcode");
}


void EJavaBytecode::exec_f2i(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented f2i opcode");
}


void EJavaBytecode::exec_f2l(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented f2l opcode");
}


void EJavaBytecode::exec_f2d(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented f2d opcode");
}


void EJavaBytecode::exec_d2i(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented d2i opcode");
}


void EJavaBytecode::exec_d2l(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented d2l opcode");
}


void EJavaBytecode::exec_d2f(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented d2f opcode");
}


void EJavaBytecode::exec_i2b(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented i2b opcode");
}


void EJavaBytecode::exec_i2c(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented i2c opcode");
}


void EJavaBytecode::exec_i2s(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented i2s opcode");
}


void EJavaBytecode::exec_lcmp(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lcmp opcode");
}


void EJavaBytecode::exec_fcmpl(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fcmpl opcode");
}


void EJavaBytecode::exec_fcmpg(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented fcmpg opcode");
}


void EJavaBytecode::exec_dcmpl(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dcmpl opcode");
}


void EJavaBytecode::exec_dcmpg(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dcmpg opcode");
}


void EJavaBytecode::exec_ifeq(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifeq opcode");
}


void EJavaBytecode::exec_ifne(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifne opcode");
}


void EJavaBytecode::exec_iflt(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented iflt opcode");
}


void EJavaBytecode::exec_ifge(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifge opcode");
}


void EJavaBytecode::exec_ifgt(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifgt opcode");
}


void EJavaBytecode::exec_ifle(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifle opcode");
}


void EJavaBytecode::exec_if_icmpeq(EADDR_T loc,EOPSIZE_T opcode)
{
  //EBytecodeObject *o=popObj();
  // TODO: check type of o, case if necessary(?)
  //UINT val1=o->val;
  //o=popObj();
  // TODO: check type of o, case if necessary(?)
  //UINT val2=o->val;
  // TODO: compare val1 and val2
  // If equal, jump to offset given (8 or 16 bit?)
  cpuDebugger("Unimplemented if_icmpeq opcode");
}


void EJavaBytecode::exec_if_icmpne(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented if_icmpne opcode");
}


void EJavaBytecode::exec_if_icmplt(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented if_icmplt opcode");
}


void EJavaBytecode::exec_if_icmpge(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented if_icmpge opcode");
}


void EJavaBytecode::exec_if_icmpgt(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented if_icmpgt opcode");
}


void EJavaBytecode::exec_if_icmple(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented if_icmple opcode");
}


void EJavaBytecode::exec_if_acmpeq(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented if_acmpeq opcode");
}


void EJavaBytecode::exec_ifacmpne(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifacmpne opcode");
}


void EJavaBytecode::exec_goto(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented goto opcode");
}


void EJavaBytecode::exec_jsr(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented jsr opcode");
}


void EJavaBytecode::exec_ret(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ret opcode");
}


void EJavaBytecode::exec_tableswitch(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented tableswitch opcode");
}


void EJavaBytecode::exec_lookupswitch(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lookupswitch opcode");
}


void EJavaBytecode::exec_ireturn(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ireturn opcode");
}


void EJavaBytecode::exec_lreturn(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented lreturn opcode");
}


void EJavaBytecode::exec_freturn(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented freturn opcode");
}


void EJavaBytecode::exec_dreturn(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented dreturn opcode");
}


void EJavaBytecode::exec_areturn(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented areturn opcode");
}


void EJavaBytecode::exec_return(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented return opcode");
}


void EJavaBytecode::exec_getstatic(EADDR_T loc,EOPSIZE_T opcode)
{
  UINT num=0;
  num=myMap->read16b(loc+1);
  BSymbol *sym=myMap->getSymtab()->lookupStrByNum(num);
  if(!sym) {
    cpuDebugger("exec_getstatic didn't find needed constant!\n");
    return;
  }
  DEBUG_OUT<<"getstatic num="<<num<<" type="<<sym->getSymType()<<"\n";
  if(sym->getSymType()==ECPU_TYPE_FIELDREF) {
    EBytecodeObject o;
    o.type=sym->getVal1();
    o.name=sym->getVal2();
    BSymbol *val=myMap->getSymtab()->lookupStrByNum(sym->getVal2());
    o.val=val->getVal1();
    o.len=0;
    pushObj(&o);
    DEBUG_OUT<<"getstatic["<<o.type<<","<<o.name<<"] ";
    DEBUG_OUT<<sym->getSymbolName()<<" ";   // field name?
    s[0]=0;
    getNameString(s,o.type); // class?
    DEBUG_OUT<<s<<" ";
    s[0]=0;
    getNameString(s,o.name); // type?
    DEBUG_OUT<<s<<"\n";
  }
  else {
    cpuDebugger("Bad getstatic constant type!");
  }
}


void EJavaBytecode::exec_putstatic(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putstatic opcode");
}


void EJavaBytecode::exec_getfield(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented getfield opcode");
}


void EJavaBytecode::exec_putfield(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putfield opcode");
}


void EJavaBytecode::exec_invokevirtual(EADDR_T loc,EOPSIZE_T opcode)
{
  invoke_helper(loc,opcode);
}


void EJavaBytecode::exec_invokespecial(EADDR_T loc,EOPSIZE_T opcode)
{
  invoke_helper(loc,opcode);
}


void EJavaBytecode::exec_invokestatic(EADDR_T loc,EOPSIZE_T opcode)
{
  invoke_helper(loc,opcode);
}


void EJavaBytecode::exec_invokeinterface(EADDR_T loc,EOPSIZE_T opcode)
{
  invoke_helper(loc,opcode);
}


void EJavaBytecode::exec_new(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented new opcode");
}


void EJavaBytecode::exec_newarray(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented newarray opcode");
}


void EJavaBytecode::exec_anewarray(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented anewarray opcode");
}


void EJavaBytecode::exec_arraylength(EADDR_T loc,EOPSIZE_T opcode)
{
  EBytecodeObject *o=popObj();
  // TODO: Check type of o, must be array
  UINT len=o->len;
  EBytecodeObject theLen;
  theLen.type=ECPU_TYPE_INTEGER;
  theLen.val=len;
  pushObj(&theLen);
}


void EJavaBytecode::exec_athrow(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented athrow opcode");
}


void EJavaBytecode::exec_checkcast(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented checkcast opcode");
}


void EJavaBytecode::exec_instanceof(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented instanceof opcode");
}


void EJavaBytecode::exec_monitorenter(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented monitorenter opcode");
}


void EJavaBytecode::exec_monitorexit(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented monitorexit opcode");
}


void EJavaBytecode::exec_wide(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented wide opcode");
}


void EJavaBytecode::exec_multinewarray(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented multinewarray opcode");
}


void EJavaBytecode::exec_ifnull(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifnull opcode");
}


void EJavaBytecode::exec_ifnonnull(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ifnonnull opcode");
}


void EJavaBytecode::exec_goto_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented goto_w opcode");
}


void EJavaBytecode::exec_jsr_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented jsr_w opcode");
}


void EJavaBytecode::exec_breakpoint(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented breakpoint opcode");
}


void EJavaBytecode::exec_ldc_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ldc_quick opcode");
}


void EJavaBytecode::exec_ldc_w_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ldc_w_quick opcode");
}


void EJavaBytecode::exec_ldc2_w_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented ldc2_w_quick opcode");
}


void EJavaBytecode::exec_getfield_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented getfield_quick opcode");
}


void EJavaBytecode::exec_putfield_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putfield_quick opcode");
}


void EJavaBytecode::exec_getfield2_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented getfield2_quick opcode");
}


void EJavaBytecode::exec_putfield2_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putfield2_quick opcode");
}


void EJavaBytecode::exec_getstatic_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented getstatic_quick opcode");
}


void EJavaBytecode::exec_putstatic_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putstatic_quick opcode");
}


void EJavaBytecode::exec_getstatic2_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented getstatic2_quick opcode");
}


void EJavaBytecode::exec_putstatic2_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putstatic2_quick opcode");
}


void EJavaBytecode::exec_invokevirtual_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokevirtual_quick opcode");
}


void EJavaBytecode::exec_invokenonvirtual_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokenonvirtual_quick opcode");
}


void EJavaBytecode::exec_invokesuper_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokesuper_quick opcode");
}


void EJavaBytecode::exec_invokestatic_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokestatic_quick opcode");
}


void EJavaBytecode::exec_invokeinterface_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokeinterface_quick opcode");
}


void EJavaBytecode::exec_invokevirtualobject_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokevirtualobject_quick opcode");
}


void EJavaBytecode::exec_new_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented new_quick opcode");
}


void EJavaBytecode::exec_anewarray_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented anewarray_quick opcode");
}


void EJavaBytecode::exec_multinewarray_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented multinewarray_quick opcode");
}


void EJavaBytecode::exec_checkcast_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented checkcast_quick opcode");
}


void EJavaBytecode::exec_instanceof_quick(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented instanceof_quick opcode");
}


void EJavaBytecode::exec_invokevirtual_quick_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented invokevirtual_quick_w opcode");
}


void EJavaBytecode::exec_getfield_quick_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented getfield_quick_w opcode");
}


void EJavaBytecode::exec_putfield_quick_w(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented putfield_quick_w opcode");
}


void EJavaBytecode::exec_impdep1(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented impdep1 opcode");
}


void EJavaBytecode::exec_impdep2(EADDR_T loc,EOPSIZE_T opcode)
{
  cpuDebugger("Unimplemented impdep2 opcode");
}


#endif
