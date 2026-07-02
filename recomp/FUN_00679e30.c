// ============================================
// Address:  0x00679e30
// Original: FUN_00679e30
// Status:   unreviewed
// ============================================


undefined4 FUN_00679e30(int *param_1,undefined4 param_2)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  
  piVar1 = (int *)param_1[7];
  if (piVar1 == (int *)0x0) {
    return 0xffffff7f;
  }
  iVar3 = FUN_0069d720(param_2,0x20);
  *param_1 = iVar3;
  if (iVar3 != 0) {
    return 0xffffff7a;
  }
  iVar3 = FUN_0069d720(param_2,8);
  param_1[1] = iVar3;
  iVar3 = FUN_0069d720(param_2,0x20);
  param_1[2] = iVar3;
  iVar3 = FUN_0069d720(param_2,0x20);
  param_1[3] = iVar3;
  iVar3 = FUN_0069d720(param_2,0x20);
  param_1[4] = iVar3;
  iVar3 = FUN_0069d720(param_2,0x20);
  param_1[5] = iVar3;
  bVar2 = FUN_0069d720(param_2,4);
  *piVar1 = 1 << (bVar2 & 0x1f);
  bVar2 = FUN_0069d720(param_2,4);
  iVar3 = 1 << (bVar2 & 0x1f);
  piVar1[1] = iVar3;
  if ((((0 < param_1[2]) && (0 < param_1[1])) && (7 < *piVar1)) && (*piVar1 <= iVar3)) {
    iVar3 = FUN_0069d720(param_2,1);
    if (iVar3 == 1) {
      return 0;
    }
  }
  FUN_00679b90(param_1);
  return 0xffffff7b;
}

