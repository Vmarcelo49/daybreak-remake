// ============================================
// Address:  0x006791c0
// Original: FUN_006791c0
// Status:   unreviewed
// ============================================


undefined4 FUN_006791c0(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x58) < 4) {
    if (*(int *)(param_1 + 0x58) < 3) {
      return 0xffffff7f;
    }
    if (*(int *)(param_1 + 4) == 0) {
      iVar1 = *(int *)(param_1 + 0x48);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x60) * 0x20 + *(int *)(param_1 + 0x48);
    }
    iVar1 = FUN_0067aa40(param_1 + 0x1e0,iVar1);
    if (iVar1 != 0) {
      return 0xffffff77;
    }
    FUN_0067a270(param_1 + 0x1e0,param_1 + 0x250);
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x70) = 0;
    *(undefined4 *)(param_1 + 0x58) = 4;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x74) = 0;
  }
  return 0;
}

