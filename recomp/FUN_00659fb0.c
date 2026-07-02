// ============================================
// Address:  0x00659fb0
// Original: FUN_00659fb0
// Status:   unreviewed
// ============================================


undefined4 FUN_00659fb0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    iVar3 = FUN_0065a850(param_1);
    if (iVar3 == 0) {
      iVar3 = FUN_0065a850(param_1);
      if (iVar3 == 0) {
        return 0;
      }
      piVar4 = (int *)FUN_0065a850(param_1);
      if ((int *)*piVar4 != (int *)0x0) {
        (**(code **)(*(int *)*piVar4 + 4))(1);
      }
      FUN_0065a7f0(param_1);
    }
    else {
      piVar4 = (int *)FUN_0065a850(param_1);
      if (*piVar4 != 0) {
        FUN_0065a3f0(1);
      }
      FUN_0065a7f0(param_1);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

