// Function: FUN_00686b00
// Address:  0x00686b00
// Source:   batch_decompile (mass dump)
// Hash:     fa81e4d135f8c857


void __thiscall FUN_00686b00(int param_1,int param_2)

{
  if (param_2 == 0) {
    FUN_00686b30();
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 1;
    *(int *)(param_1 + 0x28) = param_2;
  }
  return;
}

