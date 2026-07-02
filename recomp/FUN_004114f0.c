// ============================================
// Address:  0x004114f0
// Original: FUN_004114f0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_004114f0(int param_1)

{
  char cVar1;
  int local_8;
  
  cVar1 = FUN_00650f70();
  if (cVar1 != '\0') {
    FUN_00650f40();
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    FUN_00655d60(0,0);
    FUN_00655d60(0x43c80000,0xc1a00000);
    for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
      FUN_00655830(0x43c80000,(float)local_8 * 48.0 + 285.0,*(int *)(param_1 + 0x1f0) != local_8,
                   local_8);
    }
    FUN_00650fd0();
  }
  return 1;
}

