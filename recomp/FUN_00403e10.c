// ============================================
// Address:  0x00403e10
// Original: FUN_00403e10
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00403e10(undefined4 param_1)

{
  char cVar1;
  
  cVar1 = FUN_00650f70(param_1);
  if (cVar1 != '\0') {
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
    FUN_00655d60(0,0);
    FUN_00650fd0();
  }
  return 1;
}

