// ============================================
// Address:  0x0065cb90
// Original: FUN_0065cb90
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0065cb90(int param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_3 < 0) ||
     ((*(int *)(param_1 + 0x3c) <= param_3 &&
      ((*(int *)(param_1 + 0x3c) < param_3 || (*(uint *)(param_1 + 0x38) < param_2)))))) {
    uVar1 = 1;
  }
  else {
    *(uint *)(param_1 + 0x20) = param_2;
    *(int *)(param_1 + 0x24) = param_3;
    uVar1 = 0;
  }
  return uVar1;
}

