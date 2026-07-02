// ============================================
// Address:  0x00415890
// Original: FUN_00415890
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00415890(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_c;
  int local_8;
  
  if ((param_2 < 1) || ((int)DAT_006cfdd0 <= DAT_006cfdcc + 1)) {
    uVar1 = 0;
  }
  else if ((&DAT_006cfdd1)[param_2] == '\0') {
    FUN_0065d670(param_1);
    (&DAT_006cfdd1)[param_2] = 1;
    (&DAT_006cfdf1)[param_2] = 0;
    local_8 = 0;
    for (local_c = 1; local_c < 8; local_c = local_c + 1) {
      if ((&DAT_006cfdd1)[local_c] != '\0') {
        local_8 = local_8 + 1;
      }
    }
    DAT_006cfdcc = local_8;
    _memset(&DAT_006cfdfc,0,0x20);
    FUN_0064aed0(0);
    FUN_0065d6a0();
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

