// ============================================
// Address:  0x0068b2d0
// Original: FUN_0068b2d0
// Status:   unreviewed
// ============================================


undefined4 FUN_0068b2d0(int param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 4) & 8) == 0) {
    *param_2 = 0;
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_00686ed0(*(undefined4 *)(param_1 + 0x3c));
    *param_2 = iVar2;
    if (*param_2 == 0) {
      uVar1 = 0x8007000e;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

