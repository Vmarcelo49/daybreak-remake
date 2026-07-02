// ============================================
// Address:  0x00432810
// Original: FUN_00432810
// Status:   unreviewed
// ============================================


void __thiscall FUN_00432810(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  if (((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10)) % 4 == 0) &&
     (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 4U >> 2)) {
    FUN_00432c10(1);
  }
  uVar1 = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
  local_c = uVar1 >> 2;
  if (*(uint *)(param_1 + 8) <= local_c) {
    local_c = local_c - *(int *)(param_1 + 8);
  }
  if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0) {
    uVar2 = FUN_004107e0(4);
    *(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4) = uVar2;
  }
  FUN_00426480(*(int *)(*(int *)(param_1 + 4) + local_c * 4) + (uVar1 % 4) * 4,param_2);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

