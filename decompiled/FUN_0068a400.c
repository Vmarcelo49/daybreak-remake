// Function: FUN_0068a400
// Address:  0x0068a400
// Source:   batch_decompile (mass dump)
// Hash:     7e59d919b8393465


undefined4 __fastcall FUN_0068a400(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = 0x80040209;
  }
  else {
    uVar1 = (**(code **)(**(int **)(param_1 + 0x18) + 0x40))(*(undefined4 *)(param_1 + 0x18));
  }
  return uVar1;
}

