// Function: FUN_00435920
// Address:  0x00435920
// Source:   batch_decompile (mass dump)
// Hash:     3c47e607a3a8077f


undefined4 __fastcall FUN_00435920(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = 0;
  }
  else if (*(int *)(param_1 + 0x40) < *(int *)(param_1 + 0x10)) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x18) == *(int *)(param_1 + 8)) {
      *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
    *(undefined4 *)(param_1 + 0x40) = 0;
    if (*(int *)(param_1 + 0x18) == 0) {
      *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}

