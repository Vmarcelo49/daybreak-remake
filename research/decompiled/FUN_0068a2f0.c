// Function: FUN_0068a2f0
// Address:  0x0068a2f0
// Source:   batch_decompile (mass dump)
// Hash:     734c549f1cdc0f7a


undefined4 __fastcall FUN_0068a2f0(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = 0x80040209;
  }
  else {
    uVar1 = (**(code **)(**(int **)(param_1 + 0x18) + 0x38))(*(undefined4 *)(param_1 + 0x18));
  }
  return uVar1;
}

