#ifndef CPULIB_EJVM_H
#define CPULIB_EJVM_H


#ifdef NEMU_INCLUDE_JAVA


#include "../../nemu/cpulib/EBytecodeCPU.h"

//#include "njava.h"

//#include "../../myjava/NJLoaderLib/NJavaClassDecoder.h"


class EStack;
class EMapAbstract;
class BSymbol;


// Address modes
#define EJVM_ADDR_NONE 0
#define EJVM_ADDR_ONE 1
#define EJVM_ADDR_TWO 2
#define EJVM_ADDR_IMM8 3
#define EJVM_ADDR_IMM16 4
#define EJVM_ADDR_SPECIAL 5
#define EJVM_ADDR_ILLEGAL 6


class EJavaBytecode : public EBytecodeCPU
{
public:
  // Public member functions
  EJavaBytecode(EMapAbstract *aMap=NULL);
  virtual ~EJavaBytecode();
  static bool recognizeName(const char *name);
  virtual const char *getName();
  virtual void setKind(const char *name);
  virtual void execute();
  virtual void handle_int(EADDR_T value);
  virtual void cause_int(EADDR_T value);
  virtual void ints();
  virtual bool setRegister(const char *name,EOPSIZE_T value);
  virtual EOPSIZE_T readRegister(const char *name);
  virtual EADDR_T readStack() { return sp; }
  virtual EADDR_T disasm(EADDR_T loc);
  virtual UINT printAddrMode(EADDR_T loc,EOPSIZE_T tOpcode,UINT mode);
  virtual void resetCpu();
  virtual void wregs();
  // Public data members
protected:
  // Private member functions
  virtual void init();
  void exec_nop(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aconst_null(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_m1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_4(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iconst_5(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lconst_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lconst_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fconst_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fconst_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fconst_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dconst_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dconst_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_bipush(EADDR_T loc,EOPSIZE_T opcode);
  void exec_sipush(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldc(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldc_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldc2_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iload_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iload_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iload_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iload_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lload_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lload_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lload_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lload_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fload_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fload_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fload_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fload_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dload_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dload_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dload_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dload_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aload_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aload_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aload_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aload_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iaload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_laload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_faload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_daload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aaload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_baload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_caload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_saload(EADDR_T loc,EOPSIZE_T opcode);
  void exec_istore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lstore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fstore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dstore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_astore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_istore_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_istore_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_istore_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_istore_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lstore_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lstore_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lstore_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lstore_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fstore_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fstore_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fstore_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fstore_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dstore_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dstore_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dstore_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dstore_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_astore_0(EADDR_T loc,EOPSIZE_T opcode);
  void exec_astore_1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_astore_2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_astore_3(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_aastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_bastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_castore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_sastore(EADDR_T loc,EOPSIZE_T opcode);
  void exec_pop(EADDR_T loc,EOPSIZE_T opcode);
  void exec_pop2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dup(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dup_x1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dup_x2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dup2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dup2_x1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dup2_x2(EADDR_T loc,EOPSIZE_T opcode);
  void exec_swap(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iadd(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ladd(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fadd(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dadd(EADDR_T loc,EOPSIZE_T opcode);
  void exec_isub(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lsub(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fsub(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dsub(EADDR_T loc,EOPSIZE_T opcode);
  void exec_imul(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lmul(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fmul(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dmul(EADDR_T loc,EOPSIZE_T opcode);
  void exec_idiv(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldiv(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fdiv(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ddiv(EADDR_T loc,EOPSIZE_T opcode);
  void exec_irem(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lrem(EADDR_T loc,EOPSIZE_T opcode);
  void exec_frem(EADDR_T loc,EOPSIZE_T opcode);
  void exec_drem(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ineg(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lneg(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fneg(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dneg(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ishl(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lshl(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ishr(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lshr(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iushr(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lushr(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iand(EADDR_T loc,EOPSIZE_T opcode);
  void exec_land(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ior(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lor(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ixor(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lxor(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iinc(EADDR_T loc,EOPSIZE_T opcode);
  void exec_i2l(EADDR_T loc,EOPSIZE_T opcode);
  void exec_i2f(EADDR_T loc,EOPSIZE_T opcode);
  void exec_i2d(EADDR_T loc,EOPSIZE_T opcode);
  void exec_l2i(EADDR_T loc,EOPSIZE_T opcode);
  void exec_l2f(EADDR_T loc,EOPSIZE_T opcode);
  void exec_l2d(EADDR_T loc,EOPSIZE_T opcode);
  void exec_f2i(EADDR_T loc,EOPSIZE_T opcode);
  void exec_f2l(EADDR_T loc,EOPSIZE_T opcode);
  void exec_f2d(EADDR_T loc,EOPSIZE_T opcode);
  void exec_d2i(EADDR_T loc,EOPSIZE_T opcode);
  void exec_d2l(EADDR_T loc,EOPSIZE_T opcode);
  void exec_d2f(EADDR_T loc,EOPSIZE_T opcode);
  void exec_i2b(EADDR_T loc,EOPSIZE_T opcode);
  void exec_i2c(EADDR_T loc,EOPSIZE_T opcode);
  void exec_i2s(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lcmp(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fcmpl(EADDR_T loc,EOPSIZE_T opcode);
  void exec_fcmpg(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dcmpl(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dcmpg(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifeq(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifne(EADDR_T loc,EOPSIZE_T opcode);
  void exec_iflt(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifge(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifgt(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifle(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_icmpeq(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_icmpne(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_icmplt(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_icmpge(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_icmpgt(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_icmple(EADDR_T loc,EOPSIZE_T opcode);
  void exec_if_acmpeq(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifacmpne(EADDR_T loc,EOPSIZE_T opcode);
  void exec_goto(EADDR_T loc,EOPSIZE_T opcode);
  void exec_jsr(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ret(EADDR_T loc,EOPSIZE_T opcode);
  void exec_tableswitch(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lookupswitch(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ireturn(EADDR_T loc,EOPSIZE_T opcode);
  void exec_lreturn(EADDR_T loc,EOPSIZE_T opcode);
  void exec_freturn(EADDR_T loc,EOPSIZE_T opcode);
  void exec_dreturn(EADDR_T loc,EOPSIZE_T opcode);
  void exec_areturn(EADDR_T loc,EOPSIZE_T opcode);
  void exec_return(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getstatic(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putstatic(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getfield(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putfield(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokevirtual(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokespecial(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokestatic(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokeinterface(EADDR_T loc,EOPSIZE_T opcode);
  void exec_new(EADDR_T loc,EOPSIZE_T opcode);
  void exec_newarray(EADDR_T loc,EOPSIZE_T opcode);
  void exec_anewarray(EADDR_T loc,EOPSIZE_T opcode);
  void exec_arraylength(EADDR_T loc,EOPSIZE_T opcode);
  void exec_athrow(EADDR_T loc,EOPSIZE_T opcode);
  void exec_checkcast(EADDR_T loc,EOPSIZE_T opcode);
  void exec_instanceof(EADDR_T loc,EOPSIZE_T opcode);
  void exec_monitorenter(EADDR_T loc,EOPSIZE_T opcode);
  void exec_monitorexit(EADDR_T loc,EOPSIZE_T opcode);
  void exec_wide(EADDR_T loc,EOPSIZE_T opcode);
  void exec_multinewarray(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifnull(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ifnonnull(EADDR_T loc,EOPSIZE_T opcode);
  void exec_goto_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_jsr_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_breakpoint(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldc_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldc_w_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_ldc2_w_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getfield_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putfield_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getfield2_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putfield2_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getstatic_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putstatic_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getstatic2_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putstatic2_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokevirtual_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokenonvirtual_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokesuper_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokestatic_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokeinterface_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokevirtualobject_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_new_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_anewarray_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_multinewarray_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_checkcast_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_instanceof_quick(EADDR_T loc,EOPSIZE_T opcode);
  void exec_invokevirtual_quick_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_getfield_quick_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_putfield_quick_w(EADDR_T loc,EOPSIZE_T opcode);
  void exec_impdep1(EADDR_T loc,EOPSIZE_T opcode);
  void exec_impdep2(EADDR_T loc,EOPSIZE_T opcode);
  // misc helper methods
  void invoke_helper(EADDR_T loc,EOPSIZE_T opcode);
  void aload_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void iload_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void lload_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void fload_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void dload_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void astore_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void istore_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void lstore_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void fstore_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void dstore_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void iconst_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void lconst_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void fconst_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  void dconst_helper(EADDR_T loc,EOPSIZE_T opcode,UINT num);
  // symbol helper methods
  void getStringAtAddr(char *s,ESIZE_T len,EADDR_T addr);
  UINT getNameString(char *s,UINT index);
  UINT getNameStringVal(char *s,UINT index);
  UINT getNameStringVal2(char *s,UINT index);
  UINT getNameStringMisc(char *s,UINT index);
  void getConstant(BSymbol *c,UINT num);
  // Private data members
  char s[256];
};


#endif


#endif // CPULIB_JVM_H
