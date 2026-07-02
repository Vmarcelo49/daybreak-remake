// ============================================
// Address:  0x0067d1a0
// Original: FUN_0067d1a0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int * FUN_0067d1a0(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  size_t asStack_3c [4];
  int iStack_2c;
  int local_1c;
  int local_18;
  int local_10;
  
  if (*(int *)(param_2[1] + 0x1f8) == 0) {
    return (int *)0x0;
  }
  iVar1 = *param_2;
  iStack_2c = *(int *)(param_3 + 0x484) << 2;
  asStack_3c[3] = param_1;
  asStack_3c[2] = 0x67d1d8;
  piVar3 = (int *)FUN_0067a2c0();
  iVar2 = *(int *)(param_2[1] + 0x200);
  iStack_2c = 0x67d1f8;
  local_1c = 0;
  if (0 < *(int *)(param_3 + 0x484)) {
    piVar7 = piVar3;
    do {
      asStack_3c[4 - iVar2] = iVar1 * 4;
      asStack_3c[3 - iVar2] = param_1;
      asStack_3c[2 - iVar2] = 0x67d233;
      iVar4 = FUN_0067a2c0();
      *piVar7 = iVar4;
      local_18 = 0;
      if (0 < iVar1) {
        param_2 = (int *)0x0;
        do {
          piVar5 = (int *)(&stack0xffffffd8 + iVar2 * -4);
          iVar4 = (int)param_2;
          iVar6 = iVar2;
          if (0 < iVar2) {
            do {
              *piVar5 = *(int *)((param_4 - (int)piVar3) + (int)piVar7) + iVar4;
              iVar6 = iVar6 + -1;
              iVar4 = iVar4 + 4;
              piVar5 = piVar5 + 1;
            } while (iVar6 != 0);
          }
          piVar5 = (int *)(&stack0xffffffd8 + iVar2 * -4);
          asStack_3c[4 - iVar2] = (size_t)&LAB_0067d300;
          asStack_3c[3 - iVar2] = 4;
          asStack_3c[2 - iVar2] = iVar2;
          asStack_3c[1 - iVar2] = (size_t)piVar5;
          asStack_3c[-iVar2] = 0x67d27b;
          _qsort((void *)asStack_3c[1 - iVar2],asStack_3c[2 - iVar2],asStack_3c[3 - iVar2],
                 (_PtFuncCompare *)asStack_3c[4 - iVar2]);
          iVar4 = (int)param_2;
          local_10 = iVar2;
          if (0 < iVar2) {
            do {
              iVar6 = *piVar5;
              piVar5 = piVar5 + 1;
              *(int *)(*piVar7 + -4 + iVar4 + 4) =
                   iVar6 - *(int *)((param_4 - (int)piVar3) + (int)piVar7) >> 2;
              local_10 = local_10 + -1;
              iVar4 = iVar4 + 4;
            } while (local_10 != 0);
          }
          local_18 = local_18 + iVar2;
          param_2 = (int *)((int)param_2 + iVar2 * 4);
        } while (local_18 < iVar1);
      }
      local_1c = local_1c + 1;
      piVar7 = piVar7 + 1;
    } while (local_1c < *(int *)(param_3 + 0x484));
  }
  return piVar3;
}

