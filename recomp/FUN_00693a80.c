// ============================================
// Address:  0x00693a80
// Original: FUN_00693a80
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00693a80(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_8;
  
  local_8 = FUN_00693690(param_1);
  do {
    if (local_8 == 0) {
      return 1;
    }
    uVar1 = FUN_006936e0(&local_8);
    iVar2 = FUN_006938a0(uVar1);
  } while (iVar2 != 0);
  return 0;
}

