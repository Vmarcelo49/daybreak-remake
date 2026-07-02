// ============================================
// Address:  0x00693750
// Original: FUN_00693750
// Status:   unreviewed
// ============================================


int __thiscall FUN_00693750(undefined4 param_1,int param_2)

{
  int iVar1;
  int local_8;
  
  local_8 = FUN_00693690(param_1);
  while( true ) {
    if (local_8 == 0) {
      return 0;
    }
    iVar1 = FUN_00693720(local_8);
    if (iVar1 == param_2) break;
    local_8 = FUN_00694210(local_8);
  }
  return local_8;
}

