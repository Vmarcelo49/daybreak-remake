// Function: FUN_0069ce20
// Address:  0x0069ce20
// Source:   batch_decompile (mass dump)
// Hash:     bbfb87a96b1da36c


undefined4 FUN_0069ce20(int param_1,int param_2)

{
  param_2 = *(int *)(param_1 + 8) + param_2;
  if (*(int *)(param_1 + 4) < param_2) {
    return 0xffffffff;
  }
  *(int *)(param_1 + 8) = param_2;
  return 0;
}

