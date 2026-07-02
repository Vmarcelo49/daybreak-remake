// ============================================
// Address:  0x00680ba0
// Original: FUN_00680ba0
// Status:   unreviewed
// ============================================


void FUN_00680ba0(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)param_1[2] != (void *)0x0) {
      _free((void *)param_1[2]);
    }
    if ((void *)param_1[3] != (void *)0x0) {
      _free((void *)param_1[3]);
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
  }
  return;
}

