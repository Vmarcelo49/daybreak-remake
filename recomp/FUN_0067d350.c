// ============================================
// Address:  0x0067d350
// Original: FUN_0067d350
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_0067d350(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  size_t asStack_30 [4];
  undefined4 uStack_20;
  int local_8;
  
  iVar1 = *param_1;
  iVar2 = *(int *)(param_1[1] + 0x200);
  uStack_20 = 0x67d37b;
  iVar3 = *(int *)(param_1[1] + 0x1fc);
  iVar8 = iVar2;
  for (iVar9 = iVar3; iVar9 < iVar1; iVar9 = iVar9 + iVar8) {
    if (iVar1 < iVar9 + iVar8) {
      iVar8 = iVar1 - iVar9;
    }
    if (0 < iVar8) {
      iVar4 = param_2 + iVar9 * 4;
      piVar6 = (int *)(&stack0xffffffe4 + iVar2 * -4);
      iVar7 = iVar8;
      do {
        *piVar6 = iVar4;
        iVar4 = iVar4 + 4;
        piVar6 = piVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    asStack_30[4 - iVar2] = (size_t)&LAB_0067d300;
    asStack_30[3 - iVar2] = 4;
    asStack_30[2 - iVar2] = iVar8;
    asStack_30[1 - iVar2] = (size_t)(&stack0xffffffe4 + iVar2 * -4);
    asStack_30[-iVar2] = 0x67d3c7;
    _qsort((void *)asStack_30[1 - iVar2],asStack_30[2 - iVar2],asStack_30[3 - iVar2],
           (_PtFuncCompare *)asStack_30[4 - iVar2]);
    if (0 < iVar8) {
      iVar4 = 0;
      local_8 = iVar8;
      do {
        iVar5 = iVar4 + iVar3 * -4;
        iVar7 = iVar4 + iVar2 * -4;
        iVar4 = iVar4 + 4;
        *(int *)(iVar5 + iVar9 * 4 + param_3) = *(int *)(&stack0xffffffe4 + iVar7) - param_2 >> 2;
        local_8 = local_8 + -1;
      } while (local_8 != 0);
    }
  }
  return;
}

