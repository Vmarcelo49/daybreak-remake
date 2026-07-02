// ============================================
// Address:  0x00683de0
// Original: FUN_00683de0
// Status:   unreviewed
// ============================================


undefined4
FUN_00683de0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int *param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = param_5;
  if (0 < param_5) {
    do {
      if (*param_4 != 0) {
        iVar3 = iVar3 + 1;
      }
      param_4 = param_4 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (iVar3 != 0) {
      uVar1 = FUN_00683e20(param_1,param_2,param_3,param_5);
      return uVar1;
    }
  }
  return 0;
}

