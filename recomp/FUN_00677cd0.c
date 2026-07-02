// ============================================
// Address:  0x00677cd0
// Original: FUN_00677cd0
// Status:   unreviewed
// ============================================


int FUN_00677cd0(undefined4 *param_1)

{
  int iVar1;
  
  if (param_1[0x16] != 1) {
    return -0x83;
  }
  param_1[0x16] = 2;
  if (param_1[1] != 0) {
    iVar1 = FUN_00677d20(param_1);
    if (iVar1 != 0) {
      *param_1 = 0;
      FUN_006777e0(param_1);
    }
    return iVar1;
  }
  param_1[0x16] = 3;
  return 0;
}

