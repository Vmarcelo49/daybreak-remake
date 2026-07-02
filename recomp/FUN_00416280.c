// ============================================
// Address:  0x00416280
// Original: FUN_00416280
// Status:   unreviewed
// ============================================


void __thiscall FUN_00416280(int param_1,undefined4 param_2)

{
  int local_18;
  undefined1 local_14 [8];
  undefined4 local_c;
  int local_8;
  
  *(int *)(param_1 + 0x164) = *(int *)(param_1 + 0x164) + 1;
  if (*(int *)(param_1 + 0x164) % 0x1e == 0) {
    FUN_00416410();
    local_c = param_2;
    FUN_00415d30(0,local_14,0,8);
  }
  local_8 = 0;
  for (local_18 = 1; local_18 < 8; local_18 = local_18 + 1) {
    if (*(int *)(param_1 + 0x140 + local_18 * 4) != 0) {
      local_8 = local_8 + 1;
    }
  }
  *(bool *)(param_1 + 0x160) = DAT_006cfdcc <= local_8;
  return;
}

