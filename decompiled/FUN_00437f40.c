// Function: FUN_00437f40
// Address:  0x00437f40
// Source:   batch_decompile (mass dump)
// Hash:     62fbe8f86c6ea4e9


void __thiscall FUN_00437f40(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  if (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 1U) {
    FUN_00437370(1);
  }
  local_c = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 8) <= local_c) {
    local_c = local_c - *(int *)(param_1 + 8);
  }
  if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0) {
    uVar1 = FUN_00437630(1);
    *(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4) = uVar1;
  }
  FUN_00437650(*(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4),param_2);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

