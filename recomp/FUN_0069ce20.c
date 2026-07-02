// ============================================
// Address:  0x0069ce20
// Original: FUN_0069ce20
// Status:   unreviewed
// ============================================


undefined4 FUN_0069ce20(int param_1,int param_2)

{
  param_2 = *(int *)(param_1 + 8) + param_2;
  if (*(int *)(param_1 + 4) < param_2) {
    return 0xffffffff;
  }
  *(int *)(param_1 + 8) = param_2;
  return 0;
}

