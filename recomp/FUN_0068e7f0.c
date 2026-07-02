// ============================================
// Address:  0x0068e7f0
// Original: FUN_0068e7f0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068e7f0(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0068da80();
  if (iVar1 == 0) {
    FUN_00691bf0();
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_00691b70();
    if (iVar1 == 1) {
      FUN_00691bf0();
      uVar2 = 0;
    }
    else {
      iVar1 = (**(code **)(*param_1 + 0xa0))();
      if ((iVar1 == 1) && (param_2 != 0)) {
        FUN_00691bf0();
        uVar2 = 0;
      }
      else {
        FUN_00691c10();
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}

