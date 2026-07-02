// ============================================
// Address:  0x00693c50
// Original: FUN_00693c50
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00693c50(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_8;
  
  local_8 = FUN_00693690(param_1);
  while( true ) {
    if (local_8 == 0) {
      return 1;
    }
    uVar1 = FUN_00693720(local_8);
    param_2 = FUN_00693b30(param_2,uVar1);
    if (param_2 == 0) break;
    local_8 = FUN_00694210(local_8);
  }
  return 0;
}

