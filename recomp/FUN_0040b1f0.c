// ============================================
// Address:  0x0040b1f0
// Original: FUN_0040b1f0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0040b1f0(int param_1)

{
  char cVar1;
  
  FUN_00650f40();
  cVar1 = FUN_00650f70();
  if (cVar1 != '\0') {
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
    if (*(char *)(param_1 + 0x3c41) == '\0') {
      FUN_0040b2b0();
    }
    else {
      FUN_0040cd00();
    }
    if (*(char *)(param_1 + 0x3c42) != '\0') {
      FUN_00651860(0,0,0x44480000,0x44160000,(uint)*(byte *)(param_1 + 0x3c42) << 0x18);
    }
    FUN_00650fd0();
  }
  return 1;
}

