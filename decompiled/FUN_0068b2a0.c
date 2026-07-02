// Function: FUN_0068b2a0
// Address:  0x0068b2a0
// Source:   batch_decompile (mass dump)
// Hash:     74b5c9b7df0008a4


undefined4 FUN_0068b2a0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x14) < param_2) {
    uVar1 = 0x8004020d;
  }
  else {
    *(int *)(param_1 + 0x10) = param_2;
    uVar1 = 0;
  }
  return uVar1;
}

