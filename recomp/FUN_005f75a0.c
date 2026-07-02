// ============================================
// Address:  0x005f75a0
// Original: FUN_005f75a0
// Status:   unreviewed
// ============================================


void __fastcall FUN_005f75a0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_004244e0(0);
  iVar1 = FUN_0063bf40();
  if (*(int *)(param_1 + 0x158) + 1 < iVar1) {
    do {
      iVar3 = *(int *)(param_1 + 0x158) + 1;
      FUN_004244e0(0);
      iVar3 = FUN_00424370(iVar3);
      if (*(int *)(param_1 + 0x154) < *(int *)(iVar3 + 4)) goto LAB_005f7650;
      *(int *)(param_1 + 0x158) = *(int *)(param_1 + 0x158) + 1;
    } while (*(int *)(param_1 + 0x158) + 1 < iVar1);
    *(int *)(param_1 + 0x158) = iVar1 + -1;
LAB_005f7650:
    uVar2 = *(undefined4 *)(param_1 + 0x158);
    FUN_004244e0(0);
    uVar2 = FUN_00424370(uVar2);
    *(undefined4 *)(param_1 + 0x10) = uVar2;
  }
  return;
}

