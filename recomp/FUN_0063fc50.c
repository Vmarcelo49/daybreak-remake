// ============================================
// Address:  0x0063fc50
// Original: FUN_0063fc50
// Status:   unreviewed
// ============================================


void __thiscall FUN_0063fc50(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  if (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 1U) {
    FUN_0063ff70(1);
  }
  local_c = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 8) <= local_c) {
    local_c = local_c - *(int *)(param_1 + 8);
  }
  if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0) {
    uVar1 = FUN_00640170(1);
    *(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4) = uVar1;
  }
  FUN_00640190(*(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4),param_2);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

