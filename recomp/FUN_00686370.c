// ============================================
// Address:  0x00686370
// Original: FUN_00686370
// Status:   unreviewed
// ============================================


undefined4 FUN_00686370(int param_1,undefined4 *param_2,int param_3,undefined4 *param_4)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_2[5];
  FUN_006863f0(param_1,iVar2,param_2);
  if (param_3 != 0) {
    FUN_00686550(param_4,*(undefined4 *)(param_2[2] + *(int *)(param_1 + 0x1c) * 4),
                 param_2[*(int *)(param_1 + 0x1c) + 3],*param_2,param_3,param_2[1],
                 *(undefined4 *)(param_3 + param_2[1] * 4),(float)*(int *)(iVar2 + 0x10));
    return 1;
  }
  for (uVar1 = param_2[*(int *)(param_1 + 0x1c) + 3] & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_4 = 0;
    param_4 = param_4 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)param_4 = 0;
    param_4 = (undefined4 *)((int)param_4 + 1);
  }
  return 0;
}

