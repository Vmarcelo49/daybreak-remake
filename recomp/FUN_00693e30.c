// ============================================
// Address:  0x00693e30
// Original: FUN_00693e30
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00693e30(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int local_c;
  int local_8;
  
  if (param_2 != 0) {
    local_8 = param_2;
    local_c = 0;
    while (local_8 != 0) {
      local_8 = FUN_0068de10();
      local_c = local_c + 1;
    }
    if (param_3[1] != 0) {
      FUN_006940b0(*param_1);
    }
    if (*param_1 != 0) {
      FUN_00687260(param_3[1]);
    }
    if (*param_3 == 0) {
      *param_3 = *param_1;
    }
    iVar1 = FUN_0068dc80();
    *param_1 = iVar1;
    if (*param_1 == 0) {
      param_1[1] = 0;
    }
    param_3[1] = param_2;
    if (*param_1 != 0) {
      FUN_00687260(0);
    }
    FUN_006940b0(0);
    param_1[2] = param_1[2] - local_c;
    param_3[2] = param_3[2] + local_c;
  }
  return 1;
}

