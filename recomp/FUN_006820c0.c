// ============================================
// Address:  0x006820c0
// Original: FUN_006820c0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

undefined4 FUN_006820c0(int *param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  float *pfVar10;
  undefined4 *puVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  float *pfVar14;
  undefined4 *puVar15;
  float fVar16;
  float *pfVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  int *piVar22;
  int iVar23;
  undefined1 *puVar24;
  undefined1 *puVar25;
  undefined1 *puVar26;
  undefined1 *puVar27;
  float fVar28;
  float10 fVar29;
  int aiStack_c8 [14];
  float fStack_90;
  int aiStack_8c [4];
  undefined4 local_6c;
  float *local_50;
  undefined1 *local_4c;
  int *local_48;
  float *local_44;
  float *local_40;
  float local_3c;
  float *local_38;
  float *local_34;
  int local_30;
  int local_2c;
  float local_28;
  undefined1 *local_24;
  float *local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  float *local_8;
  
  piVar9 = param_1;
  iVar19 = *(int *)(param_1[0x10] + 4);
  local_c = *(int *)(param_1[0x10] + 0x68);
  local_44 = (float *)param_1[0x1a];
  iVar21 = *(int *)(iVar19 + 4);
  local_18 = *(int *)(iVar19 + 0x1c);
  local_24 = (undefined1 *)param_1[9];
  aiStack_8c[3] = 0x6820ff;
  iVar7 = iVar21 * -4;
  local_4c = &stack0xffffff84 + iVar7;
  local_14 = iVar19;
  aiStack_8c[3 - iVar21] = iVar21 * 4;
  aiStack_8c[2 - iVar21] = (int)param_1;
  aiStack_8c[1 - iVar21] = 0x682109;
  local_2c = FUN_0067a2c0();
  aiStack_8c[1 - iVar21] = *(int *)(iVar19 + 4) << 2;
  aiStack_8c[-iVar21] = (int)param_1;
  (&fStack_90)[-iVar21] = 9.562765e-39;
  puVar11 = (undefined4 *)FUN_0067a2c0();
  (&fStack_90)[-iVar21] = (float)(*(int *)(iVar19 + 4) << 2);
  aiStack_c8[0xd - iVar21] = (int)param_1;
  aiStack_c8[0xc - iVar21] = 0x682129;
  local_48 = (int *)FUN_0067a2c0();
  pfVar14 = local_44;
  iVar2 = *(int *)(iVar19 + 4);
  local_3c = local_44[1];
  aiStack_8c[3 - iVar21] = 0x682148;
  iVar8 = iVar2 * -4;
  iVar3 = param_1[7];
  local_8 = *(float **)(local_18 + 0x220 + iVar3 * 4);
  param_1 = (int *)0x0;
  local_10 = ((-(uint)(iVar3 != 0) & 2) + (int)pfVar14[2]) * 0x30 + *(int *)(local_c + 0x38);
  piVar9[10] = iVar3;
  if (0 < *(int *)(iVar19 + 4)) {
    fVar28 = (float)(int)local_24;
    local_1c = (int)local_24 / 2 << 2;
    local_30 = local_2c - (int)(&stack0xffffff84 + iVar8 + iVar7);
    local_20 = (float *)(&stack0xffffff84 + iVar8 + iVar7);
    do {
      iVar23 = *piVar9;
      local_50 = (float *)(4.0 / fVar28);
      aiStack_8c[(3 - iVar2) - iVar21] = local_1c;
      aiStack_8c[(2 - iVar2) - iVar21] = (int)piVar9;
      pfVar14 = *(float **)(iVar23 + (int)param_1 * 4);
      aiStack_8c[(1 - iVar2) - iVar21] = 0x6821cf;
      uVar12 = FUN_0067a2c0();
      *(undefined4 *)(local_30 + (int)local_20) = uVar12;
      aiStack_8c[(1 - iVar2) - iVar21] = (int)&local_50;
      aiStack_8c[-iVar21 - iVar2] = 0x6821e1;
      fVar29 = (float10)FUN_00682a40();
      iVar23 = piVar9[7];
      iVar4 = piVar9[6];
      aiStack_8c[-iVar21 - iVar2] = piVar9[8];
      iVar18 = local_18;
      (&fStack_90)[-iVar21 - iVar2] = (float)iVar23;
      iVar23 = local_c;
      aiStack_c8[(0xd - iVar2) - iVar21] = iVar4;
      local_40 = (float *)(float)fVar29;
      aiStack_c8[(0xc - iVar2) - iVar21] = iVar18;
      aiStack_c8[(0xb - iVar2) - iVar21] = iVar23 + 4;
      aiStack_c8[(10 - iVar2) - iVar21] = (int)pfVar14;
      aiStack_c8[(9 - iVar2) - iVar21] = 0x682201;
      FUN_00681c30();
      iVar4 = local_c;
      iVar23 = piVar9[7];
      aiStack_c8[(9 - iVar2) - iVar21] = *(undefined4 *)(local_30 + (int)local_20);
      aiStack_c8[(8 - iVar2) - iVar21] = (int)pfVar14;
      aiStack_c8[(7 - iVar2) - iVar21] = **(undefined4 **)(iVar4 + 0xc + iVar23 * 4);
      aiStack_c8[(6 - iVar2) - iVar21] = 0x68221e;
      FUN_006817a0();
      iVar4 = local_c;
      iVar23 = piVar9[7];
      aiStack_c8[(6 - iVar2) - iVar21] = (int)pfVar14;
      aiStack_c8[(5 - iVar2) - iVar21] = iVar4 + 0x14 + iVar23 * 0xc;
      aiStack_c8[(4 - iVar2) - iVar21] = 0x682232;
      FUN_0067f3d0();
      aiStack_c8[(4 - iVar2) - iVar21] = (int)pfVar14;
      aiStack_c8[(3 - iVar2) - iVar21] = 0x682238;
      fVar29 = (float10)FUN_00682a40();
      pfVar17 = local_20;
      puVar13 = local_24 + -1;
      local_34 = (float *)0x1;
      *pfVar14 = (float)(fVar29 + (float10)(float)local_40);
      *local_20 = (float)(fVar29 + (float10)(float)local_40);
      if (1 < (int)puVar13) {
        local_38 = pfVar14 + 1;
        do {
          fVar16 = local_38[1];
          fVar1 = *local_38;
          aiStack_8c[(3 - iVar2) - iVar21] = (int)&local_28;
          local_28 = fVar1 * fVar1 + fVar16 * fVar16;
          aiStack_8c[(2 - iVar2) - iVar21] = 0x68227f;
          fVar29 = (float10)FUN_00682a40();
          fVar29 = fVar29 * (float10)0.5 + (float10)(float)local_40;
          pfVar14[(int)local_34 + 1 >> 1] = (float)fVar29;
          if ((float10)*local_20 < fVar29) {
            *local_20 = (float)fVar29;
          }
          local_34 = (float *)((int)local_34 + 2);
          local_38 = local_38 + 2;
          pfVar17 = local_20;
        } while ((int)local_34 < (int)(local_24 + -1));
      }
      if (0.0 < *pfVar17) {
        *pfVar17 = 0.0;
      }
      if (local_3c < *pfVar17) {
        local_3c = *pfVar17;
      }
      local_20 = pfVar17 + 1;
      param_1 = (int *)((int)param_1 + 1);
    } while ((int)param_1 < *(int *)(iVar19 + 4));
  }
  iVar23 = local_10;
  pfVar14 = (float *)((int)local_24 / 2);
  aiStack_8c[(3 - iVar2) - iVar21] = (int)pfVar14 << 2;
  aiStack_8c[(2 - iVar2) - iVar21] = (int)piVar9;
  local_1c = (int)pfVar14 << 2;
  aiStack_8c[(1 - iVar2) - iVar21] = 0x68231d;
  local_38 = (float *)FUN_0067a2c0();
  aiStack_8c[(1 - iVar2) - iVar21] = local_1c;
  aiStack_8c[-iVar21 - iVar2] = (int)piVar9;
  (&fStack_90)[-iVar21 - iVar2] = 9.563506e-39;
  local_34 = (float *)FUN_0067a2c0();
  param_1 = (int *)0x0;
  if (0 < *(int *)(iVar19 + 4)) {
    local_30 = local_2c - (int)(&stack0xffffff84 + iVar8 + iVar7);
    iVar4 = (iVar8 + iVar7) - (int)local_48;
    piVar22 = local_48;
    local_40 = local_8;
    do {
      iVar19 = local_30;
      local_40 = local_40 + 1;
      pfVar17 = local_40;
      aiStack_8c[(3 - iVar2) - iVar21] = 0x3c;
      aiStack_8c[(2 - iVar2) - iVar21] = (int)piVar9;
      local_28 = *pfVar17;
      iVar19 = *(int *)((int)piVar22 + (int)(&stack0xffffff84 + iVar4 + iVar19));
      iVar23 = *(int *)(*piVar9 + (int)param_1 * 4);
      local_20 = (float *)(local_1c + iVar23);
      piVar9[10] = iVar3;
      aiStack_8c[(1 - iVar2) - iVar21] = 0x682399;
      puVar15 = (undefined4 *)FUN_0067a2c0();
      *piVar22 = (int)puVar15;
      for (iVar18 = 0xf; iVar18 != 0; iVar18 = iVar18 + -1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      if (0 < (int)pfVar14) {
        iVar19 = iVar19 - (int)local_20;
        pfVar17 = local_20;
        local_50 = pfVar14;
        do {
          aiStack_8c[(3 - iVar2) - iVar21] = iVar19 + (int)pfVar17;
          aiStack_8c[(2 - iVar2) - iVar21] = 0x6823cb;
          fVar29 = (float10)FUN_00682a40();
          *pfVar17 = (float)fVar29;
          pfVar17 = pfVar17 + 1;
          local_50 = (float *)((int)local_50 + -1);
        } while (local_50 != (float *)0x0);
      }
      iVar19 = local_10;
      pfVar17 = local_20;
      aiStack_8c[(3 - iVar2) - iVar21] = (int)local_38;
      aiStack_8c[(2 - iVar2) - iVar21] = (int)pfVar17;
      aiStack_8c[(1 - iVar2) - iVar21] = iVar19;
      aiStack_8c[-iVar21 - iVar2] = 0x6823ed;
      FUN_0067c2b0();
      pfVar17 = local_34;
      fVar28 = local_3c;
      aiStack_8c[-iVar21 - iVar2] = *(undefined4 *)(&stack0xffffff84 + iVar4 + (int)piVar22);
      iVar19 = local_10;
      (&fStack_90)[-iVar21 - iVar2] = fVar28;
      aiStack_c8[(0xd - iVar2) - iVar21] = (int)pfVar17;
      aiStack_c8[(0xc - iVar2) - iVar21] = iVar23;
      aiStack_c8[(0xb - iVar2) - iVar21] = iVar19;
      aiStack_c8[(10 - iVar2) - iVar21] = 0x68240a;
      FUN_0067c970();
      iVar19 = local_10;
      pfVar10 = local_34;
      pfVar17 = local_38;
      aiStack_c8[(10 - iVar2) - iVar21] = iVar23;
      aiStack_c8[(9 - iVar2) - iVar21] = 1;
      aiStack_c8[(8 - iVar2) - iVar21] = (int)pfVar10;
      aiStack_c8[(7 - iVar2) - iVar21] = (int)pfVar17;
      aiStack_c8[(6 - iVar2) - iVar21] = iVar19;
      aiStack_c8[(5 - iVar2) - iVar21] = 0x68241e;
      FUN_0067ce60();
      iVar19 = local_c;
      pfVar17 = local_20;
      fVar28 = local_8[(int)local_28 + 0x101];
      if (*(int *)(local_18 + 800 + (int)fVar28 * 4) != 1) {
        return 0xffffffff;
      }
      aiStack_8c[(3 - iVar2) - iVar21] = iVar23;
      aiStack_8c[(2 - iVar2) - iVar21] = (int)pfVar17;
      aiStack_8c[(1 - iVar2) - iVar21] = *(undefined4 *)(*(int *)(iVar19 + 0x30) + (int)fVar28 * 4);
      aiStack_8c[-iVar21 - iVar2] = (int)piVar9;
      (&fStack_90)[-iVar21 - iVar2] = 9.563924e-39;
      uVar12 = FUN_00684930();
      iVar19 = *piVar22;
      (&fStack_90)[-iVar21 - iVar2] = (float)piVar9;
      *(undefined4 *)(iVar19 + 0x1c) = uVar12;
      aiStack_c8[(0xd - iVar2) - iVar21] = 0x68245f;
      iVar18 = FUN_0067f350();
      iVar19 = local_10;
      pfVar10 = local_34;
      pfVar17 = local_38;
      if ((iVar18 != 0) && (*(int *)(*piVar22 + 0x1c) != 0)) {
        aiStack_8c[(3 - iVar2) - iVar21] = iVar23;
        aiStack_8c[(2 - iVar2) - iVar21] = 2;
        aiStack_8c[(1 - iVar2) - iVar21] = (int)pfVar10;
        aiStack_8c[-iVar21 - iVar2] = (int)pfVar17;
        (&fStack_90)[-iVar21 - iVar2] = (float)iVar19;
        aiStack_c8[(0xd - iVar2) - iVar21] = 0x68248b;
        FUN_0067ce60();
        pfVar10 = local_8;
        pfVar17 = local_20;
        fVar28 = local_28;
        aiStack_c8[(0xd - iVar2) - iVar21] = iVar23;
        aiStack_c8[(0xc - iVar2) - iVar21] = (int)pfVar17;
        aiStack_c8[(0xb - iVar2) - iVar21] =
             *(undefined4 *)(*(int *)(local_c + 0x30) + (int)pfVar10[(int)fVar28 + 0x101] * 4);
        aiStack_c8[(10 - iVar2) - iVar21] = (int)piVar9;
        aiStack_c8[(9 - iVar2) - iVar21] = 0x6824ad;
        uVar12 = FUN_00684930();
        pfVar10 = local_34;
        iVar19 = *piVar22;
        aiStack_c8[(9 - iVar2) - iVar21] = iVar23;
        aiStack_c8[(8 - iVar2) - iVar21] = 0;
        iVar18 = local_10;
        pfVar17 = local_38;
        *(undefined4 *)(iVar19 + 0x38) = uVar12;
        aiStack_c8[(7 - iVar2) - iVar21] = (int)pfVar10;
        aiStack_c8[(6 - iVar2) - iVar21] = (int)pfVar17;
        aiStack_c8[(5 - iVar2) - iVar21] = iVar18;
        aiStack_c8[(4 - iVar2) - iVar21] = 0x6824c6;
        FUN_0067ce60();
        pfVar10 = local_8;
        pfVar17 = local_20;
        fVar28 = local_28;
        aiStack_c8[(4 - iVar2) - iVar21] = iVar23;
        aiStack_c8[(3 - iVar2) - iVar21] = (int)pfVar17;
        aiStack_c8[(2 - iVar2) - iVar21] =
             *(undefined4 *)(*(int *)(local_c + 0x30) + (int)pfVar10[(int)fVar28 + 0x101] * 4);
        aiStack_c8[(1 - iVar2) - iVar21] = (int)piVar9;
        aiStack_c8[-iVar21 - iVar2] = 0x6824e8;
        uVar12 = FUN_00684930();
        local_50 = (float *)0x4;
        iVar19 = 0x10000;
        *(undefined4 *)*piVar22 = uVar12;
        do {
          puVar15 = (undefined4 *)*piVar22;
          uVar12 = *puVar15;
          aiStack_8c[(3 - iVar2) - iVar21] = iVar19 / 7;
          pfVar17 = local_8;
          aiStack_8c[(2 - iVar2) - iVar21] = puVar15[7];
          fVar28 = local_28;
          aiStack_8c[(1 - iVar2) - iVar21] = uVar12;
          aiStack_8c[-iVar21 - iVar2] =
               *(undefined4 *)(*(int *)(local_c + 0x30) + (int)pfVar17[(int)fVar28 + 0x101] * 4);
          (&fStack_90)[-iVar21 - iVar2] = (float)piVar9;
          aiStack_c8[(0xd - iVar2) - iVar21] = 0x682535;
          uVar12 = FUN_006854d0();
          iVar19 = iVar19 + 0x10000;
          *(undefined4 *)(*piVar22 + (int)local_50) = uVar12;
          local_50 = local_50 + 1;
        } while (iVar19 < 0x70000);
        local_50 = (float *)0x20;
        iVar19 = 0x10000;
        do {
          iVar23 = *piVar22;
          uVar12 = *(undefined4 *)(iVar23 + 0x1c);
          aiStack_8c[(3 - iVar2) - iVar21] = iVar19 / 7;
          pfVar17 = local_8;
          aiStack_8c[(2 - iVar2) - iVar21] = *(undefined4 *)(iVar23 + 0x38);
          fVar28 = local_28;
          aiStack_8c[(1 - iVar2) - iVar21] = uVar12;
          aiStack_8c[-iVar21 - iVar2] =
               *(undefined4 *)(*(int *)(local_c + 0x30) + (int)pfVar17[(int)fVar28 + 0x101] * 4);
          (&fStack_90)[-iVar21 - iVar2] = (float)piVar9;
          aiStack_c8[(0xd - iVar2) - iVar21] = 0x68259b;
          uVar12 = FUN_006854d0();
          iVar19 = iVar19 + 0x10000;
          *(undefined4 *)(*piVar22 + (int)local_50) = uVar12;
          local_50 = local_50 + 1;
        } while (iVar19 < 0x70000);
      }
      param_1 = (int *)((int)param_1 + 1);
      piVar22 = piVar22 + 1;
      iVar23 = local_10;
      iVar19 = local_14;
    } while ((int)param_1 < *(int *)(local_14 + 4));
  }
  local_44[1] = local_3c;
  iVar4 = *(int *)(iVar19 + 4);
  aiStack_8c[(3 - iVar2) - iVar21] = 0x6825fa;
  puVar13 = &stack0xffffff84 + iVar4 * -0x10 + iVar8 + iVar7;
  aiStack_8c[((3 - iVar4) - iVar2) - iVar21] = 0x68260a;
  local_38 = (float *)(&stack0xffffff84 + iVar4 * -8 + iVar8 + iVar7);
  aiStack_8c[((iVar4 * -2 + 3) - iVar2) - iVar21] = 0x68261a;
  local_40 = (float *)(&stack0xffffff84 + iVar4 * -0xc + iVar8 + iVar7);
  aiStack_8c[((iVar4 * -3 + 3) - iVar2) - iVar21] = 0x68262a;
  pfVar14 = local_8;
  iVar18 = local_18;
  if (local_8[0x121] != 0.0) {
    aiStack_8c[((iVar4 * -4 + 3) - iVar2) - iVar21] = local_2c;
    aiStack_8c[((iVar4 * -4 + 2) - iVar2) - iVar21] = (int)pfVar14;
    aiStack_8c[((iVar4 * -4 + 1) - iVar2) - iVar21] = iVar23;
    aiStack_8c[(iVar4 * -4 - iVar2) - iVar21] = iVar18 + 0xb34;
    (&fStack_90)[(iVar4 * -4 - iVar2) - iVar21] = (float)piVar9;
    aiStack_c8[((iVar4 * -4 + 0xd) - iVar2) - iVar21] = 0x682652;
    local_6c = FUN_0067cef0();
    aiStack_c8[((iVar4 * -4 + 0xd) - iVar2) - iVar21] = local_6c;
    aiStack_c8[((iVar4 * -4 + 0xc) - iVar2) - iVar21] = (int)local_8;
    aiStack_c8[((iVar4 * -4 + 0xb) - iVar2) - iVar21] = iVar23;
    aiStack_c8[((iVar4 * -4 + 10) - iVar2) - iVar21] = (int)piVar9;
    aiStack_c8[((iVar4 * -4 + 9) - iVar2) - iVar21] = 0x682661;
    local_20 = (float *)FUN_0067d1a0();
  }
  puVar15 = (undefined4 *)(&stack0xffffff84 + iVar4 * -0x10 + iVar8 + iVar7);
  for (uVar20 = *(uint *)(iVar19 + 4) & 0x3fffffff; uVar20 != 0; uVar20 = uVar20 - 1) {
    *puVar15 = 0;
    puVar15 = puVar15 + 1;
  }
  for (iVar19 = 0; iVar19 != 0; iVar19 = iVar19 + -1) {
    *(undefined1 *)puVar15 = 0;
    puVar15 = (undefined4 *)((int)puVar15 + 1);
  }
  puVar27 = &stack0xffffff84 + iVar4 * -0x10 + iVar8 + iVar7;
  if ((*(int *)(*(int *)(local_10 + 4) + 500) != 0) &&
     (param_1 = (int *)0x0, puVar27 = &stack0xffffff84 + iVar4 * -0x10 + iVar8 + iVar7,
     0 < *(int *)(local_14 + 4))) {
    uVar20 = (uint)local_24 & 0x3fffffff;
    iVar19 = local_2c - (int)(&stack0xffffff84 + iVar4 * -0x10 + iVar8 + iVar7);
    puVar24 = &stack0xffffff84 + iVar4 * -0x10 + iVar8 + iVar7;
    do {
      uVar12 = *(undefined4 *)(puVar13 + iVar19);
      *(undefined4 *)(puVar24 + -4) = 0x6826da;
      iVar2 = local_10;
      iVar21 = -(uVar20 * 2 + 3 & 0xfffffffc);
      puVar27 = puVar24 + iVar21;
      *(int *)(puVar24 + iVar21 + -4) = (int)puVar24 + iVar21;
      *(undefined4 *)(puVar24 + iVar21 + -8) = uVar12;
      *(int *)(puVar24 + iVar21 + -0xc) = iVar2;
      *(int *)puVar13 = (int)puVar24 + iVar21;
      *(undefined4 *)(puVar24 + iVar21 + -0x10) = 0x6826e9;
      FUN_0067d350();
      param_1 = (int *)((int)param_1 + 1);
      puVar13 = puVar13 + 4;
      puVar24 = puVar24 + iVar21;
    } while ((int)param_1 < *(int *)(local_14 + 4));
  }
  *(int **)(puVar27 + -4) = piVar9;
  *(undefined4 *)(puVar27 + -8) = 0x682706;
  iVar19 = FUN_0067f350();
  *(int **)(puVar27 + -8) = piVar9;
  uVar20 = -(uint)(iVar19 != 0) & 0xfffffff9;
  fVar28 = (float)(uVar20 + 7);
  local_28 = fVar28;
  *(undefined4 *)(puVar27 + -0xc) = 0x68271b;
  iVar19 = FUN_0067f350();
  if ((int)fVar28 <= (int)((-(uint)(iVar19 != 0) & 7) + 7)) {
    local_50 = local_44 + uVar20 + 10;
    puVar13 = puVar27;
    do {
      piVar22 = piVar9 + 1;
      *(undefined4 *)(puVar13 + -4) = 1;
      *(undefined4 *)(puVar13 + -8) = 0;
      *(int **)(puVar13 + -0xc) = piVar22;
      *(undefined4 *)(puVar13 + -0x10) = 0x682747;
      FUN_0069d4c0();
      *(undefined4 *)(puVar13 + -0x10) = *(undefined4 *)(local_c + 0x2c);
      *(int *)(puVar13 + -0x14) = iVar3;
      *(int **)(puVar13 + -0x18) = piVar22;
      *(undefined4 *)(puVar13 + -0x1c) = 0x682758;
      FUN_0069d4c0();
      if (piVar9[7] != 0) {
        iVar19 = piVar9[6];
        *(undefined4 *)(puVar13 + -4) = 1;
        *(int *)(puVar13 + -8) = iVar19;
        *(int **)(puVar13 + -0xc) = piVar22;
        *(undefined4 *)(puVar13 + -0x10) = 0x68276e;
        FUN_0069d4c0();
        iVar19 = piVar9[8];
        *(undefined4 *)(puVar13 + -0x10) = 1;
        *(int *)(puVar13 + -0x14) = iVar19;
        *(int **)(puVar13 + -0x18) = piVar22;
        *(undefined4 *)(puVar13 + -0x1c) = 0x68277a;
        FUN_0069d4c0();
      }
      param_1 = (int *)0x0;
      if (0 < *(int *)(local_14 + 4)) {
        iVar21 = (int)local_48 - (int)puVar11;
        local_44 = local_8 + 1;
        local_3c = (float)((int)local_4c - (int)puVar11);
        iVar19 = local_2c - (int)puVar11;
        local_24 = &stack0xffffff84 + ((iVar4 * -0x10 + iVar8 + iVar7) - (int)puVar11);
        puVar15 = puVar11;
        do {
          local_30 = *(int *)(iVar19 + (int)puVar15);
          fVar28 = *local_44;
          iVar2 = *piVar9;
          *(int *)(puVar13 + -4) = local_1c;
          *(int **)(puVar13 + -8) = piVar9;
          iVar2 = *(int *)(iVar2 + (int)param_1 * 4);
          *(undefined4 *)(puVar13 + -0xc) = 0x6827e3;
          local_34 = (float *)FUN_0067a2c0();
          *puVar15 = local_34;
          *(float **)(puVar13 + -0xc) = local_34;
          pfVar14 = local_8;
          *(undefined4 *)(puVar13 + -0x10) =
               *(undefined4 *)(*(int *)(iVar21 + (int)puVar15) + (int)local_28 * 4);
          *(undefined4 *)(puVar13 + -0x14) =
               *(undefined4 *)(*(int *)(local_c + 0x30) + (int)pfVar14[(int)fVar28 + 0x101] * 4);
          *(int **)(puVar13 + -0x18) = piVar9;
          *(undefined4 *)(puVar13 + -0x1c) = 0x682813;
          uVar12 = FUN_00685580();
          iVar23 = local_30;
          pfVar14 = local_34;
          *(undefined4 *)((int)local_3c + (int)puVar15) = uVar12;
          *(undefined4 *)(puVar13 + -0x1c) =
               *(undefined4 *)(local_18 + ((int)local_28 + (piVar9[7] + 0x36) * 0xf) * 4);
          iVar18 = local_10;
          *(int *)(puVar13 + -0x20) = iVar2;
          *(float **)(puVar13 + -0x24) = pfVar14;
          *(int *)(puVar13 + -0x28) = iVar23;
          *(int *)(puVar13 + -0x2c) = iVar18;
          *(undefined4 *)(puVar13 + -0x30) = 0x682843;
          FUN_0067c250();
          iVar23 = local_10;
          iVar18 = local_1c + iVar2;
          *(undefined4 *)(puVar13 + -0x30) = *(undefined4 *)(local_24 + (int)puVar15);
          *(int *)(puVar13 + -0x34) = iVar18;
          *(int *)(puVar13 + -0x38) = iVar2;
          *(int *)(puVar13 + -0x3c) = iVar23;
          *(undefined4 *)(puVar13 + -0x40) = 0x68285a;
          FUN_0067d420();
          local_44 = local_44 + 1;
          param_1 = (int *)((int)param_1 + 1);
          puVar15 = puVar15 + 1;
          fVar28 = local_28;
        } while ((int)param_1 < *(int *)(local_14 + 4));
      }
      pfVar14 = local_8;
      iVar19 = local_18;
      puVar27 = local_4c;
      if (local_8[0x121] != 0.0) {
        *(undefined4 *)(puVar13 + -4) =
             *(undefined4 *)(local_18 + ((int)fVar28 + (piVar9[7] + 0x36) * 0xf) * 4);
        *(undefined1 **)(puVar13 + -8) = puVar27;
        pfVar17 = local_20;
        *(undefined4 **)(puVar13 + -0xc) = puVar11;
        *(float **)(puVar13 + -0x10) = pfVar17;
        iVar21 = *piVar9;
        *(undefined4 *)(puVar13 + -0x14) = local_6c;
        iVar2 = local_10;
        *(int *)(puVar13 + -0x18) = iVar21;
        *(float **)(puVar13 + -0x1c) = pfVar14;
        *(int *)(puVar13 + -0x20) = iVar2;
        *(int *)(puVar13 + -0x24) = iVar19 + 0xb34;
        *(float *)(puVar13 + -0x28) = fVar28;
        *(undefined4 *)(puVar13 + -0x2c) = 0x6828c8;
        FUN_0067d690();
      }
      param_1 = (int *)0x0;
      puVar27 = puVar13;
      if (0 < (int)*local_8) {
        local_34 = local_8 + 0x111;
        do {
          iVar21 = 0;
          local_3c = 0.0;
          fVar28 = *local_34;
          if (0 < *(int *)(local_14 + 4)) {
            local_44 = local_8 + 1;
            pfVar14 = local_40;
            do {
              if ((int *)*local_44 == param_1) {
                *pfVar14 = 0.0;
                if (*(int *)(local_4c + iVar21 * 4) != 0) {
                  *pfVar14 = 1.4013e-45;
                }
                *(undefined4 *)
                 (&stack0xffffff84 + ((iVar4 * -4 + iVar8 + iVar7) - (int)local_40) + (int)pfVar14)
                     = *(undefined4 *)(*piVar9 + iVar21 * 4);
                *(int *)(((int)local_38 - (int)local_40) + (int)pfVar14) =
                     *(int *)(*piVar9 + iVar21 * 4) + local_1c;
                local_3c = (float)((int)local_3c + 1);
                pfVar14 = pfVar14 + 1;
              }
              iVar21 = iVar21 + 1;
              local_44 = local_44 + 1;
              iVar19 = local_18;
            } while (iVar21 < *(int *)(local_14 + 4));
          }
          iVar21 = *(int *)(iVar19 + 0x520 + (int)fVar28 * 4);
          *(float *)(puVar13 + -4) = local_3c;
          pfVar14 = local_38;
          puVar5 = (&PTR_DAT_006be808)[iVar21];
          *(float **)(puVar13 + -8) = local_40;
          iVar21 = local_c;
          *(float **)(puVar13 + -0xc) = pfVar14;
          *(undefined4 *)(puVar13 + -0x10) =
               *(undefined4 *)(*(int *)(iVar21 + 0x34) + (int)fVar28 * 4);
          *(int **)(puVar13 + -0x14) = piVar9;
          pcVar6 = *(code **)(puVar5 + 0x14);
          puVar25 = puVar13 + -0x18;
          *(undefined4 *)(puVar13 + -0x18) = 0x6829a2;
          uVar12 = (*pcVar6)();
          iVar21 = *(int *)(iVar19 + 0x520 + (int)fVar28 * 4);
          *(undefined4 *)(puVar25 + -4) = uVar12;
          pfVar14 = local_40;
          puVar5 = (&PTR_DAT_006be808)[iVar21];
          *(float *)(puVar25 + -8) = local_3c;
          pfVar17 = local_38;
          *(float **)(puVar25 + -0xc) = pfVar14;
          iVar21 = local_c;
          *(undefined4 *)(puVar25 + -0x10) = 0;
          *(float **)(puVar25 + -0x14) = pfVar17;
          *(undefined4 *)(puVar25 + -0x18) =
               *(undefined4 *)(*(int *)(iVar21 + 0x34) + (int)fVar28 * 4);
          *(int **)(puVar25 + -0x1c) = piVar9;
          pcVar6 = *(code **)(puVar5 + 0x18);
          puVar26 = puVar25 + -0x20;
          *(undefined4 *)(puVar25 + -0x20) = 0x6829cd;
          (*pcVar6)();
          local_34 = local_34 + 1;
          puVar13 = puVar26 + 0x30;
          puVar27 = puVar26 + 0x30;
          param_1 = (int *)((int)param_1 + 1);
          fVar28 = local_28;
        } while ((int)param_1 < (int)*local_8);
      }
      *(int **)(puVar27 + -4) = piVar9 + 1;
      *(undefined4 *)(puVar27 + -8) = 0x6829f9;
      FUN_0069d5c0();
      *(int **)(puVar27 + -8) = piVar9 + 1;
      *(undefined4 *)(puVar27 + -0xc) = 0x6829ff;
      fVar16 = (float)FUN_0069d7f0();
      fVar28 = (float)((int)fVar28 + 1);
      *(int **)(puVar27 + -0xc) = piVar9;
      *local_50 = fVar16;
      local_50 = local_50 + 1;
      local_28 = fVar28;
      *(undefined4 *)(puVar27 + -0x10) = 0x682a14;
      iVar19 = FUN_0067f350();
      puVar13 = puVar27;
    } while ((int)fVar28 <= (int)((-(uint)(iVar19 != 0) & 7) + 7));
  }
  return 0;
}

