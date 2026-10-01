// Function: FUN_00424270
// Address:  0x00424270
// Source:   batch_decompile (mass dump)
// Hash:     4bc7fff5bc10b326


void __thiscall FUN_00424270(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  if (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 1U) {
    FUN_00424aa0(1);
  }
  local_c = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 8) <= local_c) {
    local_c = local_c - *(int *)(param_1 + 8);
  }
  if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0) {
    uVar1 = FUN_00432bb0(1);
    *(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4) = uVar1;
  }
  FUN_00424da0(*(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4),param_2);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

