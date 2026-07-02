// ============================================
// Address:  0x0069a730
// Original: FUN_0069a730
// Status:   unreviewed
// ============================================


void FUN_0069a730(void)

{
  ushort in_FPUControlWord;
  float10 in_ST0;
  float10 in_ST1;
  
  if ((DAT_006d8980 != 0) && ((MXCSR & 0x1f80) == 0x1f80 && (in_FPUControlWord & 0x7f) == 0x7f)) {
    FUN_0069ad20();
    return;
  }
  FUN_0069a78d((double)in_ST1,(double)in_ST0);
  return;
}

