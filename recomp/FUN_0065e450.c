// ============================================
// Address:  0x0065e450
// Original: FUN_0065e450
// Status:   unreviewed
// ============================================


int FUN_0065e450(byte param_1)

{
  int iVar1;
  
  if ((param_1 < 0x61) || (0x66 < param_1)) {
    if ((param_1 < 0x41) || (0x46 < param_1)) {
      if ((param_1 < 0x30) || (0x39 < param_1)) {
        iVar1 = 0;
      }
      else {
        iVar1 = param_1 - 0x30;
      }
    }
    else {
      iVar1 = param_1 - 0x37;
    }
  }
  else {
    iVar1 = param_1 - 0x57;
  }
  return iVar1;
}

