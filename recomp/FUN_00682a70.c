// ============================================
// Address:  0x00682a70
// Original: FUN_00682a70
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

undefined4 FUN_00682a70(int *param_1,int *param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  code *pcVar8;
  undefined4 uVar9;
  uint uVar10;
  int *piVar11;
  uint *puVar12;
  int iVar13;
  float *pfVar14;
  int iVar15;
  undefined1 *puVar16;
  undefined1 *puVar17;
  undefined1 *puVar18;
  undefined1 *puVar19;
  undefined1 *puVar20;
  undefined1 *puVar21;
  undefined1 *puVar22;
  undefined4 *puVar23;
  int iVar24;
  undefined4 uStack_40;
  int local_28;
  int *local_24;
  uint *local_10;
  int *local_8;
  
  iVar3 = *(int *)(param_1[0x10] + 4);
  iVar4 = *(int *)(param_1[0x10] + 0x68);
  iVar24 = *(int *)(iVar3 + 0x1c);
  uVar5 = *(uint *)(iVar24 + param_1[7] * 4);
  param_1[9] = uVar5;
  iVar6 = *(int *)(iVar3 + 4);
  uStack_40 = 0x682ab3;
  local_10 = (uint *)(&stack0xffffffc4 + iVar6 * -0xc);
  puVar18 = &stack0xffffffc4 + iVar6 * -0x10;
  puVar16 = &stack0xffffffc4 + iVar6 * -0x10;
  (&uStack_40)[-iVar6] = 0x682ac2;
  (&uStack_40)[iVar6 * -2] = 0x682ad1;
  (&uStack_40)[iVar6 * -3] = 0x682ae0;
  iVar15 = 0;
  if (0 < iVar6) {
    local_8 = param_2;
    do {
      local_8 = local_8 + 1;
      puVar7 = (&PTR_DAT_006be800)[*(int *)(iVar24 + 800 + param_2[*local_8 + 0x101] * 4)];
      *(undefined4 *)(puVar16 + -4) =
           *(undefined4 *)(*(int *)(iVar4 + 0x30) + param_2[*local_8 + 0x101] * 4);
      *(int **)(puVar16 + -8) = param_1;
      pcVar8 = *(code **)(puVar7 + 0x14);
      puVar17 = puVar16 + -0xc;
      *(undefined4 *)(puVar16 + -0xc) = 0x682b41;
      uVar10 = (*pcVar8)();
      puVar18 = puVar17 + 8;
      puVar16 = puVar17 + 8;
      local_10[-iVar6] = uVar10;
      *local_10 = (uint)(uVar10 != 0);
      puVar23 = *(undefined4 **)(*param_1 + iVar15 * 4);
      for (uVar10 = (uVar5 & 0x3fffffff) >> 1; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar23 = 0;
        puVar23 = puVar23 + 1;
      }
      iVar15 = iVar15 + 1;
      for (iVar13 = (uVar5 & 1) << 1; iVar13 != 0; iVar13 = iVar13 + -1) {
        *(undefined1 *)puVar23 = 0;
        puVar23 = (undefined4 *)((int)puVar23 + 1);
      }
      local_10 = local_10 + 1;
    } while (iVar15 < *(int *)(iVar3 + 4));
  }
  local_8 = (int *)0x0;
  if (0 < param_2[0x121]) {
    piVar11 = param_2 + 0x222;
    do {
      if ((*(int *)(&stack0xffffffc4 + piVar11[-0x100] * 4 + iVar6 * -0xc) != 0) ||
         (*(int *)(&stack0xffffffc4 + *piVar11 * 4 + iVar6 * -0xc) != 0)) {
        *(undefined4 *)(&stack0xffffffc4 + piVar11[-0x100] * 4 + iVar6 * -0xc) = 1;
        *(undefined4 *)(&stack0xffffffc4 + *piVar11 * 4 + iVar6 * -0xc) = 1;
      }
      local_8 = (int *)((int)local_8 + 1);
      piVar11 = piVar11 + 1;
    } while ((int)local_8 < param_2[0x121]);
  }
  local_8 = (int *)0x0;
  puVar22 = puVar18;
  if (0 < *param_2) {
    local_24 = param_2 + 0x111;
    do {
      iVar13 = 0;
      iVar15 = 0;
      puVar12 = (uint *)(&stack0xffffffc4 + iVar6 * -8);
      local_10 = (uint *)param_2;
      if (0 < *(int *)(iVar3 + 4)) {
        do {
          local_10 = local_10 + 1;
          if ((int *)*local_10 == local_8) {
            *puVar12 = (uint)(*(int *)(&stack0xffffffc4 + iVar15 * 4 + iVar6 * -0xc) != 0);
            iVar13 = iVar13 + 1;
            puVar12 = puVar12 + 1;
            puVar12[iVar6 + -1] = *(uint *)(*param_1 + iVar15 * 4);
          }
          iVar15 = iVar15 + 1;
        } while (iVar15 < *(int *)(iVar3 + 4));
      }
      *(int *)(puVar18 + -4) = iVar13;
      iVar15 = *local_24;
      puVar7 = (&PTR_DAT_006be808)[*(int *)(iVar24 + 0x520 + iVar15 * 4)];
      *(undefined1 **)(puVar18 + -8) = &stack0xffffffc4 + iVar6 * -8;
      *(undefined1 **)(puVar18 + -0xc) = &stack0xffffffc4 + iVar6 * -4;
      *(undefined4 *)(puVar18 + -0x10) = *(undefined4 *)(*(int *)(iVar4 + 0x34) + iVar15 * 4);
      *(int **)(puVar18 + -0x14) = param_1;
      pcVar8 = *(code **)(puVar7 + 0x1c);
      puVar19 = puVar18 + -0x18;
      *(undefined4 *)(puVar18 + -0x18) = 0x682c83;
      (*pcVar8)();
      puVar18 = puVar19 + 0x14;
      puVar22 = puVar19 + 0x14;
      local_8 = (int *)((int)local_8 + 1);
      local_24 = local_24 + 1;
    } while ((int)local_8 < *param_2);
  }
  local_24 = (int *)param_2[0x121];
  if (-1 < (int)local_24 + -1) {
    piVar11 = param_2 + (int)local_24 + 0x221;
    do {
      pfVar14 = *(float **)(*param_1 + piVar11[-0x100] * 4);
      if (0 < (int)uVar5 / 2) {
        iVar15 = *(int *)(*param_1 + *piVar11 * 4) - (int)pfVar14;
        local_28 = (int)uVar5 / 2;
        do {
          fVar1 = *pfVar14;
          fVar2 = *(float *)(iVar15 + (int)pfVar14);
          if (fVar1 <= 0.0) {
            if (fVar2 <= 0.0) {
              *(float *)(iVar15 + (int)pfVar14) = fVar1;
              fVar2 = fVar1 - fVar2;
              goto LAB_00682d27;
            }
            *(float *)(iVar15 + (int)pfVar14) = fVar2 + fVar1;
          }
          else if (fVar2 <= 0.0) {
            *(float *)(iVar15 + (int)pfVar14) = fVar1;
            fVar2 = fVar2 + fVar1;
LAB_00682d27:
            *pfVar14 = fVar2;
          }
          else {
            *(float *)(iVar15 + (int)pfVar14) = fVar1 - fVar2;
          }
          pfVar14 = pfVar14 + 1;
          local_28 = local_28 + -1;
        } while (local_28 != 0);
      }
      piVar11 = piVar11 + -1;
      local_24 = (int *)((int)local_24 + -1);
    } while (local_24 != (int *)0x0);
  }
  iVar15 = 0;
  puVar20 = puVar22;
  piVar11 = param_2;
  if (0 < *(int *)(iVar3 + 4)) {
    do {
      iVar13 = param_2[piVar11[1] + 0x101];
      puVar7 = (&PTR_DAT_006be800)[*(int *)(iVar24 + 800 + iVar13 * 4)];
      *(undefined4 *)(puVar20 + -4) = *(undefined4 *)(*param_1 + iVar15 * 4);
      *(undefined4 *)(puVar20 + -8) = *(undefined4 *)(&stack0xffffffc4 + iVar15 * 4 + iVar6 * -0x10)
      ;
      *(undefined4 *)(puVar20 + -0xc) = *(undefined4 *)(*(int *)(iVar4 + 0x30) + iVar13 * 4);
      *(int **)(puVar20 + -0x10) = param_1;
      pcVar8 = *(code **)(puVar7 + 0x18);
      puVar21 = puVar20 + -0x14;
      *(undefined4 *)(puVar20 + -0x14) = 0x682d8d;
      (*pcVar8)();
      puVar22 = puVar21 + 0x10;
      iVar15 = iVar15 + 1;
      puVar20 = puVar21 + 0x10;
      piVar11 = piVar11 + 1;
    } while (iVar15 < *(int *)(iVar3 + 4));
  }
  iVar24 = 0;
  if (0 < *(int *)(iVar3 + 4)) {
    do {
      iVar6 = param_1[7];
      uVar9 = *(undefined4 *)(*param_1 + iVar24 * 4);
      *(undefined4 *)(puVar22 + -4) = uVar9;
      *(undefined4 *)(puVar22 + -8) = uVar9;
      *(undefined4 *)(puVar22 + -0xc) = **(undefined4 **)(iVar4 + 0xc + iVar6 * 4);
      *(undefined4 *)(puVar22 + -0x10) = 0x682dc1;
      FUN_00680be0();
      iVar24 = iVar24 + 1;
    } while (iVar24 < *(int *)(iVar3 + 4));
  }
  return 0;
}

