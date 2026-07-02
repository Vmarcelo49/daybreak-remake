// ============================================
// Address:  0x006543d0
// Original: FUN_006543d0
// Status:   unreviewed
// ============================================


undefined4 FUN_006543d0(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  
  uVar1 = FUN_006543b0();
  uVar2 = FUN_0064f010();
  if (uVar1 < uVar2) {
    piVar4 = (int *)FUN_00658a10(uVar1);
    iVar5 = FUN_00654390();
    if (*piVar4 == iVar5) {
      uVar3 = FUN_006545d0(uVar1);
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

