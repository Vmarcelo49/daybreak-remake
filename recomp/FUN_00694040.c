// ============================================
// Address:  0x00694040
// Original: FUN_00694040
// Status:   unreviewed
// ============================================


void __fastcall FUN_00694040(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_8;
  
  local_8 = *param_1;
  while (local_8 != 0) {
    local_8 = FUN_0068dc80();
    uVar2 = FUN_0068de10();
    FUN_006940b0(uVar2);
    FUN_00687260(local_8);
  }
  iVar1 = *param_1;
  *param_1 = param_1[1];
  param_1[1] = iVar1;
  return;
}

