  // Don't edit this file, it is machine generated
  switch(theOpcode) {
      case 0x0:   exec_nop(loc,theOpcode);  break;
      case 0x1:   exec_aconst_null(loc,theOpcode);  break;
      case 0x2:   exec_iconst_m1(loc,theOpcode);  break;
      case 0x3:   exec_iconst_0(loc,theOpcode);  break;
      case 0x4:   exec_iconst_1(loc,theOpcode);  break;
      case 0x5:   exec_iconst_2(loc,theOpcode);  break;
      case 0x6:   exec_iconst_3(loc,theOpcode);  break;
      case 0x7:   exec_iconst_4(loc,theOpcode);  break;
      case 0x8:   exec_iconst_5(loc,theOpcode);  break;
      case 0x9:   exec_lconst_0(loc,theOpcode);  break;
      case 0x0A:   exec_lconst_1(loc,theOpcode);  break;
      case 0x0B:   exec_fconst_0(loc,theOpcode);  break;
      case 0x0C:   exec_fconst_1(loc,theOpcode);  break;
      case 0x0D:   exec_fconst_2(loc,theOpcode);  break;
      case 0x0E:   exec_dconst_0(loc,theOpcode);  break;
      case 0x0F:   exec_dconst_1(loc,theOpcode);  break;
      case 0x10:   exec_bipush(loc,theOpcode);  break;
      case 0x11:   exec_sipush(loc,theOpcode);  break;
      case 0x12:   exec_ldc(loc,theOpcode);  break;
      case 0x13:   exec_ldc_w(loc,theOpcode);  break;
      case 0x14:   exec_ldc2_w(loc,theOpcode);  break;
      case 0x15:   exec_iload(loc,theOpcode);  break;
      case 0x16:   exec_lload(loc,theOpcode);  break;
      case 0x17:   exec_fload(loc,theOpcode);  break;
      case 0x18:   exec_dload(loc,theOpcode);  break;
      case 0x19:   exec_aload(loc,theOpcode);  break;
      case 0x1A:   exec_iload_0(loc,theOpcode);  break;
      case 0x1B:   exec_iload_1(loc,theOpcode);  break;
      case 0x1C:   exec_iload_2(loc,theOpcode);  break;
      case 0x1D:   exec_iload_3(loc,theOpcode);  break;
      case 0x1E:   exec_lload_0(loc,theOpcode);  break;
      case 0x1F:   exec_lload_1(loc,theOpcode);  break;
      case 0x20:   exec_lload_2(loc,theOpcode);  break;
      case 0x21:   exec_lload_3(loc,theOpcode);  break;
      case 0x22:   exec_fload_0(loc,theOpcode);  break;
      case 0x23:   exec_fload_1(loc,theOpcode);  break;
      case 0x24:   exec_fload_2(loc,theOpcode);  break;
      case 0x25:   exec_fload_3(loc,theOpcode);  break;
      case 0x26:   exec_dload_0(loc,theOpcode);  break;
      case 0x27:   exec_dload_1(loc,theOpcode);  break;
      case 0x28:   exec_dload_2(loc,theOpcode);  break;
      case 0x29:   exec_dload_3(loc,theOpcode);  break;
      case 0x2A:   exec_aload_0(loc,theOpcode);  break;
      case 0x2B:   exec_aload_1(loc,theOpcode);  break;
      case 0x2C:   exec_aload_2(loc,theOpcode);  break;
      case 0x2D:   exec_aload_3(loc,theOpcode);  break;
      case 0x2E:   exec_iaload(loc,theOpcode);  break;
      case 0x2F:   exec_laload(loc,theOpcode);  break;
      case 0x30:   exec_faload(loc,theOpcode);  break;
      case 0x31:   exec_daload(loc,theOpcode);  break;
      case 0x32:   exec_aaload(loc,theOpcode);  break;
      case 0x33:   exec_baload(loc,theOpcode);  break;
      case 0x34:   exec_caload(loc,theOpcode);  break;
      case 0x35:   exec_saload(loc,theOpcode);  break;
      case 0x36:   exec_istore(loc,theOpcode);  break;
      case 0x37:   exec_lstore(loc,theOpcode);  break;
      case 0x38:   exec_fstore(loc,theOpcode);  break;
      case 0x39:   exec_dstore(loc,theOpcode);  break;
      case 0x3A:   exec_astore(loc,theOpcode);  break;
      case 0x3B:   exec_istore_0(loc,theOpcode);  break;
      case 0x3C:   exec_istore_1(loc,theOpcode);  break;
      case 0x3D:   exec_istore_2(loc,theOpcode);  break;
      case 0x3E:   exec_istore_3(loc,theOpcode);  break;
      case 0x3F:   exec_lstore_0(loc,theOpcode);  break;
      case 0x40:   exec_lstore_1(loc,theOpcode);  break;
      case 0x41:   exec_lstore_2(loc,theOpcode);  break;
      case 0x42:   exec_lstore_3(loc,theOpcode);  break;
      case 0x43:   exec_fstore_0(loc,theOpcode);  break;
      case 0x44:   exec_fstore_1(loc,theOpcode);  break;
      case 0x45:   exec_fstore_2(loc,theOpcode);  break;
      case 0x46:   exec_fstore_3(loc,theOpcode);  break;
      case 0x47:   exec_dstore_0(loc,theOpcode);  break;
      case 0x48:   exec_dstore_1(loc,theOpcode);  break;
      case 0x49:   exec_dstore_2(loc,theOpcode);  break;
      case 0x4A:   exec_dstore_3(loc,theOpcode);  break;
      case 0x4B:   exec_astore_0(loc,theOpcode);  break;
      case 0x4C:   exec_astore_1(loc,theOpcode);  break;
      case 0x4D:   exec_astore_2(loc,theOpcode);  break;
      case 0x4E:   exec_astore_3(loc,theOpcode);  break;
      case 0x4F:   exec_iastore(loc,theOpcode);  break;
      case 0x50:   exec_lastore(loc,theOpcode);  break;
      case 0x51:   exec_fastore(loc,theOpcode);  break;
      case 0x52:   exec_dastore(loc,theOpcode);  break;
      case 0x53:   exec_aastore(loc,theOpcode);  break;
      case 0x54:   exec_bastore(loc,theOpcode);  break;
      case 0x55:   exec_castore(loc,theOpcode);  break;
      case 0x56:   exec_sastore(loc,theOpcode);  break;
      case 0x57:   exec_pop(loc,theOpcode);  break;
      case 0x58:   exec_pop2(loc,theOpcode);  break;
      case 0x59:   exec_dup(loc,theOpcode);  break;
      case 0x5A:   exec_dup_x1(loc,theOpcode);  break;
      case 0x5B:   exec_dup_x2(loc,theOpcode);  break;
      case 0x5C:   exec_dup2(loc,theOpcode);  break;
      case 0x5D:   exec_dup2_x1(loc,theOpcode);  break;
      case 0x5E:   exec_dup2_x2(loc,theOpcode);  break;
      case 0x5F:   exec_swap(loc,theOpcode);  break;
      case 0x60:   exec_iadd(loc,theOpcode);  break;
      case 0x61:   exec_ladd(loc,theOpcode);  break;
      case 0x62:   exec_fadd(loc,theOpcode);  break;
      case 0x63:   exec_dadd(loc,theOpcode);  break;
      case 0x64:   exec_isub(loc,theOpcode);  break;
      case 0x65:   exec_lsub(loc,theOpcode);  break;
      case 0x66:   exec_fsub(loc,theOpcode);  break;
      case 0x67:   exec_dsub(loc,theOpcode);  break;
      case 0x68:   exec_imul(loc,theOpcode);  break;
      case 0x69:   exec_lmul(loc,theOpcode);  break;
      case 0x6A:   exec_fmul(loc,theOpcode);  break;
      case 0x6B:   exec_dmul(loc,theOpcode);  break;
      case 0x6C:   exec_idiv(loc,theOpcode);  break;
      case 0x6D:   exec_ldiv(loc,theOpcode);  break;
      case 0x6E:   exec_fdiv(loc,theOpcode);  break;
      case 0x6F:   exec_ddiv(loc,theOpcode);  break;
      case 0x70:   exec_irem(loc,theOpcode);  break;
      case 0x71:   exec_lrem(loc,theOpcode);  break;
      case 0x72:   exec_frem(loc,theOpcode);  break;
      case 0x73:   exec_drem(loc,theOpcode);  break;
      case 0x74:   exec_ineg(loc,theOpcode);  break;
      case 0x75:   exec_lneg(loc,theOpcode);  break;
      case 0x76:   exec_fneg(loc,theOpcode);  break;
      case 0x77:   exec_dneg(loc,theOpcode);  break;
      case 0x78:   exec_ishl(loc,theOpcode);  break;
      case 0x79:   exec_lshl(loc,theOpcode);  break;
      case 0x7A:   exec_ishr(loc,theOpcode);  break;
      case 0x7B:   exec_lshr(loc,theOpcode);  break;
      case 0x7C:   exec_iushr(loc,theOpcode);  break;
      case 0x7D:   exec_lushr(loc,theOpcode);  break;
      case 0x7E:   exec_iand(loc,theOpcode);  break;
      case 0x7F:   exec_land(loc,theOpcode);  break;
      case 0x80:   exec_ior(loc,theOpcode);  break;
      case 0x81:   exec_lor(loc,theOpcode);  break;
      case 0x82:   exec_ixor(loc,theOpcode);  break;
      case 0x83:   exec_lxor(loc,theOpcode);  break;
      case 0x84:   exec_iinc(loc,theOpcode);  break;
      case 0x85:   exec_i2l(loc,theOpcode);  break;
      case 0x86:   exec_i2f(loc,theOpcode);  break;
      case 0x87:   exec_i2d(loc,theOpcode);  break;
      case 0x88:   exec_l2i(loc,theOpcode);  break;
      case 0x89:   exec_l2f(loc,theOpcode);  break;
      case 0x8A:   exec_l2d(loc,theOpcode);  break;
      case 0x8B:   exec_f2i(loc,theOpcode);  break;
      case 0x8C:   exec_f2l(loc,theOpcode);  break;
      case 0x8D:   exec_f2d(loc,theOpcode);  break;
      case 0x8E:   exec_d2i(loc,theOpcode);  break;
      case 0x8F:   exec_d2l(loc,theOpcode);  break;
      case 0x90:   exec_d2f(loc,theOpcode);  break;
      case 0x91:   exec_i2b(loc,theOpcode);  break;
      case 0x92:   exec_i2c(loc,theOpcode);  break;
      case 0x93:   exec_i2s(loc,theOpcode);  break;
      case 0x94:   exec_lcmp(loc,theOpcode);  break;
      case 0x95:   exec_fcmpl(loc,theOpcode);  break;
      case 0x96:   exec_fcmpg(loc,theOpcode);  break;
      case 0x97:   exec_dcmpl(loc,theOpcode);  break;
      case 0x98:   exec_dcmpg(loc,theOpcode);  break;
      case 0x99:   exec_ifeq(loc,theOpcode);  break;
      case 0x9A:   exec_ifne(loc,theOpcode);  break;
      case 0x9B:   exec_iflt(loc,theOpcode);  break;
      case 0x9C:   exec_ifge(loc,theOpcode);  break;
      case 0x9D:   exec_ifgt(loc,theOpcode);  break;
      case 0x9E:   exec_ifle(loc,theOpcode);  break;
      case 0x9F:   exec_if_icmpeq(loc,theOpcode);  break;
      case 0xA0:   exec_if_icmpne(loc,theOpcode);  break;
      case 0xA1:   exec_if_icmplt(loc,theOpcode);  break;
      case 0xA2:   exec_if_icmpge(loc,theOpcode);  break;
      case 0xA3:   exec_if_icmpgt(loc,theOpcode);  break;
      case 0xA4:   exec_if_icmple(loc,theOpcode);  break;
      case 0xA5:   exec_if_acmpeq(loc,theOpcode);  break;
      case 0xA6:   exec_ifacmpne(loc,theOpcode);  break;
      case 0xA7:   exec_goto(loc,theOpcode);  break;
      case 0xA8:   exec_jsr(loc,theOpcode);  break;
      case 0xA9:   exec_ret(loc,theOpcode);  break;
      case 0xAA:   exec_tableswitch(loc,theOpcode);  break;
      case 0xAB:   exec_lookupswitch(loc,theOpcode);  break;
      case 0xAC:   exec_ireturn(loc,theOpcode);  break;
      case 0xAD:   exec_lreturn(loc,theOpcode);  break;
      case 0xAE:   exec_freturn(loc,theOpcode);  break;
      case 0xAF:   exec_dreturn(loc,theOpcode);  break;
      case 0xB0:   exec_areturn(loc,theOpcode);  break;
      case 0xB1:   exec_return(loc,theOpcode);  break;
      case 0xB2:   exec_getstatic(loc,theOpcode);  break;
      case 0xB3:   exec_putstatic(loc,theOpcode);  break;
      case 0xB4:   exec_getfield(loc,theOpcode);  break;
      case 0xB5:   exec_putfield(loc,theOpcode);  break;
      case 0xB6:   exec_invokevirtual(loc,theOpcode);  break;
      case 0xB7:   exec_invokespecial(loc,theOpcode);  break;
      case 0xB8:   exec_invokestatic(loc,theOpcode);  break;
      case 0xB9:   exec_invokeinterface(loc,theOpcode);  break;
      case 0xBA:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xBB:   exec_new(loc,theOpcode);  break;
      case 0xBC:   exec_newarray(loc,theOpcode);  break;
      case 0xBD:   exec_anewarray(loc,theOpcode);  break;
      case 0xBE:   exec_arraylength(loc,theOpcode);  break;
      case 0xBF:   exec_athrow(loc,theOpcode);  break;
      case 0xC0:   exec_checkcast(loc,theOpcode);  break;
      case 0xC1:   exec_instanceof(loc,theOpcode);  break;
      case 0xC2:   exec_monitorenter(loc,theOpcode);  break;
      case 0xC3:   exec_monitorexit(loc,theOpcode);  break;
      case 0xC4:   exec_wide(loc,theOpcode);  break;
      case 0xC5:   exec_multinewarray(loc,theOpcode);  break;
      case 0xC6:   exec_ifnull(loc,theOpcode);  break;
      case 0xC7:   exec_ifnonnull(loc,theOpcode);  break;
      case 0xC8:   exec_goto_w(loc,theOpcode);  break;
      case 0xC9:   exec_jsr_w(loc,theOpcode);  break;
      case 0xCA:   exec_breakpoint(loc,theOpcode);  break;
      case 0xCB:   exec_ldc_quick(loc,theOpcode);  break;
      case 0xCC:   exec_ldc_w_quick(loc,theOpcode);  break;
      case 0xCD:   exec_ldc2_w_quick(loc,theOpcode);  break;
      case 0xCE:   exec_getfield_quick(loc,theOpcode);  break;
      case 0xCF:   exec_putfield_quick(loc,theOpcode);  break;
      case 0xD0:   exec_getfield2_quick(loc,theOpcode);  break;
      case 0xD1:   exec_putfield2_quick(loc,theOpcode);  break;
      case 0xD2:   exec_getstatic_quick(loc,theOpcode);  break;
      case 0xD3:   exec_putstatic_quick(loc,theOpcode);  break;
      case 0xD4:   exec_getstatic2_quick(loc,theOpcode);  break;
      case 0xD5:   exec_putstatic2_quick(loc,theOpcode);  break;
      case 0xD6:   exec_invokevirtual_quick(loc,theOpcode);  break;
      case 0xD7:   exec_invokenonvirtual_quick(loc,theOpcode);  break;
      case 0xD8:   exec_invokesuper_quick(loc,theOpcode);  break;
      case 0xD9:   exec_invokestatic_quick(loc,theOpcode);  break;
      case 0xDA:   exec_invokeinterface_quick(loc,theOpcode);  break;
      case 0xDB:   exec_invokevirtualobject_quick(loc,theOpcode);  break;
      case 0xDC:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xDD:   exec_new_quick(loc,theOpcode);  break;
      case 0xDE:   exec_anewarray_quick(loc,theOpcode);  break;
      case 0xDF:   exec_multinewarray_quick(loc,theOpcode);  break;
      case 0xE0:   exec_checkcast_quick(loc,theOpcode);  break;
      case 0xE1:   exec_instanceof_quick(loc,theOpcode);  break;
      case 0xE2:   exec_invokevirtual_quick_w(loc,theOpcode);  break;
      case 0xE3:   exec_getfield_quick_w(loc,theOpcode);  break;
      case 0xE4:   exec_putfield_quick_w(loc,theOpcode);  break;
      case 0xE5:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xE6:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xE7:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xE8:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xE9:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xEA:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xEB:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xEC:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xED:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xEE:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xEF:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF0:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF1:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF2:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF3:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF4:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF5:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF6:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF7:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF8:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xF9:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xFA:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xFB:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xFC:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xFD:   exec_ILLEGAL(loc,theOpcode);  break;  // ???
      case 0xFE:   exec_impdep1(loc,theOpcode);  break;
      case 0xFF:   exec_impdep2(loc,theOpcode);  break;
      default:  exec_INVALID("EJVM_exec.h"); break;
  }
