// ============================================
// Address:  0x00683320
// Original: FUN_00683320
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

undefined4 FUN_00683320(int param_1,int *param_2,int param_3,int param_4,code *param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  int *piVar12;
  int aiStack_50 [3];
  int local_30;
  int local_2c;
  int local_1c;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  piVar1 = (int *)*param_2;
  iVar2 = *(int *)param_2[4];
  iVar3 = piVar1[2];
  iVar5 = (piVar1[1] - *piVar1) / iVar3;
  aiStack_50[2] = 0x683369;
  iVar4 = param_4 * -4;
  puVar10 = (undefined4 *)(&stack0xffffffbc + iVar4);
  puVar9 = &stack0xffffffbc + iVar4;
  if (0 < param_4) {
    iVar7 = param_4;
    do {
      aiStack_50[2 - param_4] = ((iVar5 + -1 + iVar2) / iVar2) * 4;
      aiStack_50[1 - param_4] = param_1;
      aiStack_50[-param_4] = 0x68338b;
      uVar6 = FUN_0067a2c0();
      *puVar10 = uVar6;
      puVar10 = puVar10 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  local_c = 0;
  if (0 < param_2[2]) {
    do {
      iVar7 = 0;
      local_14 = 0;
      if (0 < iVar5) {
        local_1c = 0;
        do {
          if ((local_c == 0) && (iVar11 = 0, 0 < param_4)) {
            piVar12 = (int *)(&stack0xffffffbc + iVar4);
            do {
              *(int *)(puVar9 + -4) = param_1 + 4;
              *(int *)(puVar9 + -8) = param_2[4];
              *(undefined4 *)(puVar9 + -0xc) = 0x6833e7;
              iVar7 = FUN_0067e870();
              if (iVar7 == -1) {
                return 0;
              }
              *(undefined4 *)(local_1c + *piVar12) = *(undefined4 *)(param_2[7] + iVar7 * 4);
              if (*(int *)(local_1c + *piVar12) == 0) {
                return 0;
              }
              iVar11 = iVar11 + 1;
              piVar12 = piVar12 + 1;
              iVar7 = local_14;
            } while (iVar11 < param_4);
          }
          local_30 = 0;
          if (0 < iVar2) {
            local_8 = 0;
            local_18 = iVar7 * iVar3;
            do {
              if (iVar5 <= iVar7) break;
              local_2c = 0;
              if (0 < param_4) {
                piVar12 = (int *)(&stack0xffffffbc + iVar4);
                do {
                  iVar7 = *piVar1;
                  if (((piVar1[*(int *)(local_8 + *(int *)(local_1c + *piVar12)) + 5] &
                       1 << ((byte)local_c & 0x1f)) != 0) &&
                     (iVar11 = *(int *)(*(int *)(param_2[5] +
                                                *(int *)(local_8 + *(int *)(local_1c + *piVar12)) *
                                                4) + local_c * 4), iVar11 != 0)) {
                    *(int *)(puVar9 + -4) = iVar3;
                    *(int *)(puVar9 + -8) = param_1 + 4;
                    *(int *)(puVar9 + -0xc) =
                         *(int *)((param_3 - (int)(&stack0xffffffbc + iVar4)) + (int)piVar12) +
                         (iVar7 + local_18) * 4;
                    *(int *)(puVar9 + -0x10) = iVar11;
                    puVar8 = puVar9 + -0x14;
                    *(undefined4 *)(puVar9 + -0x14) = 0x6834bd;
                    iVar7 = (*param_5)();
                    puVar9 = puVar8 + 0x10;
                    if (iVar7 == -1) {
                      return 0;
                    }
                  }
                  local_2c = local_2c + 1;
                  piVar12 = piVar12 + 1;
                  iVar7 = local_14;
                } while (local_2c < param_4);
              }
              local_8 = local_8 + 4;
              local_30 = local_30 + 1;
              local_18 = local_18 + iVar3;
              iVar7 = iVar7 + 1;
              local_14 = iVar7;
            } while (local_30 < iVar2);
          }
          local_1c = local_1c + 4;
        } while (iVar7 < iVar5);
      }
      local_c = local_c + 1;
    } while (local_c < param_2[2]);
  }
  return 0;
}

