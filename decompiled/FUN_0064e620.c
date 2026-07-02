// Function: FUN_0064e620
// Address:  0x0064e620
// Source:   batch_decompile (mass dump)
// Hash:     6b2df7e8e5681b0d


undefined4 __thiscall FUN_0064e620(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  uVar1 = FUN_0064f010(param_1);
  if (param_2 < uVar1) {
    piVar3 = (int *)FUN_0064ef20(param_2);
    if (*piVar3 == -1) {
      puVar4 = (undefined4 *)FUN_0064ef20(param_2);
      uVar2 = FUN_006562c0(*puVar4);
    }
    else {
      puVar4 = (undefined4 *)FUN_0064ef20(*piVar3);
      uVar2 = FUN_006562c0(*puVar4);
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

