// Function: FUN_00667f20
// Address:  0x00667f20
// Source:   batch_decompile (mass dump)
// Hash:     04139f946747dcef


undefined4 __fastcall FUN_00667f20(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)(**(int **)(param_1 + 4) + 0x48))(*(undefined4 *)(param_1 + 4));
  }
  return uVar1;
}

