// ============================================
// Address:  0x006817a0
// Original: FUN_006817a0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_006817a0(int *param_1,int param_2,float *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  byte bVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  uint uVar15;
  float *pfVar16;
  int iVar17;
  int *piVar18;
  int iVar19;
  float *pfVar20;
  int iVar21;
  int aiStack_44 [4];
  undefined4 uStack_34;
  float local_24 [4];
  uint local_14;
  float *local_10;
  int local_c;
  
  iVar6 = *param_1;
  iVar14 = iVar6 >> 2;
  iVar17 = iVar6 >> 1;
  iVar19 = iVar6 >> 3;
  uStack_34 = 0x6817cf;
  iVar7 = iVar6 * -4;
  pfVar12 = (float *)(&stack0xffffffd0 + iVar7);
  iVar1 = iVar17 * 4;
  pfVar16 = (float *)(&stack0xffffffd0 + iVar1 + iVar7);
  pfVar20 = (float *)(param_2 + (iVar14 + iVar17) * 4);
  local_c = 0;
  pfVar8 = (float *)(iVar1 + param_1[2]);
  pfVar13 = pfVar20 + 1;
  if (0 < iVar19) {
    local_14 = iVar19 + 1U >> 1;
    local_c = local_14 * 2;
    pfVar9 = pfVar8;
    local_10 = pfVar16;
    do {
      fVar2 = pfVar20[-2];
      fVar3 = *pfVar13;
      fVar4 = pfVar13[2];
      pfVar20 = pfVar20 + -4;
      pfVar8 = pfVar9 + -2;
      pfVar13 = pfVar13 + 4;
      fVar5 = *pfVar20;
      *local_10 = (fVar2 + fVar3) * *pfVar8 + (fVar4 + fVar5) * pfVar9[-1];
      local_10[1] = (fVar4 + fVar5) * *pfVar8 - (fVar2 + fVar3) * pfVar9[-1];
      local_14 = local_14 - 1;
      pfVar9 = pfVar8;
      local_10 = local_10 + 2;
    } while (local_14 != 0);
  }
  pfVar13 = (float *)(param_2 + 4);
  if (local_c < iVar17 - iVar19) {
    pfVar9 = pfVar16 + local_c;
    uVar15 = ((iVar17 - iVar19) - local_c) + 1U >> 1;
    local_c = local_c + uVar15 * 2;
    pfVar10 = pfVar8;
    do {
      fVar2 = pfVar20[-2];
      fVar3 = *pfVar13;
      fVar4 = pfVar20[-4];
      pfVar20 = pfVar20 + -4;
      pfVar8 = pfVar10 + -2;
      fVar5 = pfVar13[2];
      pfVar13 = pfVar13 + 4;
      uVar15 = uVar15 - 1;
      *pfVar9 = (fVar2 - fVar3) * *pfVar8 + (fVar4 - fVar5) * pfVar10[-1];
      pfVar9[1] = (fVar4 - fVar5) * *pfVar8 - (fVar2 - fVar3) * pfVar10[-1];
      pfVar10 = pfVar8;
      pfVar9 = pfVar9 + 2;
    } while (uVar15 != 0);
  }
  pfVar20 = (float *)(param_2 + iVar6 * 4);
  if (local_c < iVar17) {
    uVar15 = (iVar17 - local_c) + 1U >> 1;
    pfVar9 = pfVar16 + local_c;
    do {
      fVar2 = pfVar20[-2];
      pfVar20 = pfVar20 + -4;
      pfVar10 = pfVar8 + -2;
      fVar3 = *pfVar13;
      fVar4 = *pfVar20;
      fVar5 = pfVar13[2];
      pfVar13 = pfVar13 + 4;
      uVar15 = uVar15 - 1;
      *pfVar9 = (-fVar2 - fVar3) * *pfVar10 + (-fVar4 - fVar5) * pfVar8[-1];
      pfVar9[1] = (-fVar4 - fVar5) * *pfVar10 - (-fVar2 - fVar3) * pfVar8[-1];
      pfVar8 = pfVar10;
      pfVar9 = pfVar9 + 2;
    } while (uVar15 != 0);
  }
  iVar19 = param_1[1];
  iVar21 = param_1[2];
  if (0 < iVar19 + -6) {
    pfVar13 = pfVar16 + iVar14 + -8 + (iVar17 - iVar14) + 7;
    pfVar20 = pfVar16 + iVar14 + -8;
    pfVar8 = (float *)(iVar21 + 0x10);
    do {
      fVar2 = pfVar13[-1];
      fVar3 = pfVar20[6];
      fVar4 = *pfVar13;
      fVar5 = pfVar20[7];
      pfVar13[-1] = pfVar20[6] + pfVar13[-1];
      *pfVar13 = pfVar20[7] + *pfVar13;
      pfVar20[6] = (fVar4 - fVar5) * pfVar8[-3] + (fVar2 - fVar3) * pfVar8[-4];
      pfVar20[7] = (fVar4 - fVar5) * pfVar8[-4] - (fVar2 - fVar3) * pfVar8[-3];
      fVar2 = pfVar13[-3];
      fVar3 = pfVar20[4];
      fVar4 = pfVar13[-2];
      fVar5 = pfVar20[5];
      pfVar13[-3] = pfVar20[4] + pfVar13[-3];
      pfVar13[-2] = pfVar13[-2] + pfVar20[5];
      pfVar20[4] = (fVar2 - fVar3) * *pfVar8 + (fVar4 - fVar5) * pfVar8[1];
      pfVar20[5] = (fVar4 - fVar5) * *pfVar8 - (fVar2 - fVar3) * pfVar8[1];
      fVar2 = pfVar13[-5];
      fVar3 = pfVar20[2];
      fVar4 = pfVar13[-4];
      fVar5 = pfVar20[3];
      pfVar13[-5] = pfVar20[2] + pfVar13[-5];
      pfVar13[-4] = pfVar20[3] + pfVar13[-4];
      pfVar20[2] = (fVar2 - fVar3) * pfVar8[4] + (fVar4 - fVar5) * pfVar8[5];
      pfVar20[3] = (fVar4 - fVar5) * pfVar8[4] - (fVar2 - fVar3) * pfVar8[5];
      fVar2 = pfVar13[-7];
      fVar3 = *pfVar20;
      fVar4 = pfVar13[-6];
      fVar5 = pfVar20[1];
      pfVar13[-7] = pfVar13[-7] + *pfVar20;
      pfVar13[-6] = pfVar20[1] + pfVar13[-6];
      pfVar9 = pfVar20 + -8;
      pfVar13 = pfVar13 + -8;
      *pfVar20 = (fVar2 - fVar3) * pfVar8[8] + (fVar4 - fVar5) * pfVar8[9];
      pfVar20[1] = (fVar4 - fVar5) * pfVar8[8] - (fVar2 - fVar3) * pfVar8[9];
      pfVar20 = pfVar9;
      pfVar8 = pfVar8 + 0x10;
    } while (pfVar16 <= pfVar9);
  }
  local_10 = (float *)(iVar19 + -7);
  bVar11 = 1;
  if (0 < (int)local_10) {
    do {
      param_2 = 1 << (bVar11 & 0x1f);
      if (0 < param_2) {
        iVar19 = iVar17 >> (bVar11 & 0x1f);
        pfVar13 = pfVar16;
        do {
          aiStack_44[4 - iVar6] = 4 << (bVar11 & 0x1f);
          aiStack_44[3 - iVar6] = iVar19;
          aiStack_44[2 - iVar6] = (int)pfVar13;
          aiStack_44[1 - iVar6] = iVar21;
          aiStack_44[-iVar6] = 0x681a6c;
          FUN_00681680();
          pfVar13 = pfVar13 + iVar19;
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
      bVar11 = bVar11 + 1;
      local_10 = (float *)((int)local_10 + -1);
    } while (local_10 != (float *)0x0);
  }
  if (0 < iVar17) {
    uVar15 = iVar17 + 0x1fU >> 5;
    do {
      aiStack_44[4 - iVar6] = (int)pfVar16;
      aiStack_44[3 - iVar6] = 0x681aa7;
      FUN_006810f0();
      pfVar16 = pfVar16 + 0x20;
      uVar15 = uVar15 - 1;
    } while (uVar15 != 0);
  }
  piVar18 = (int *)param_1[3];
  iVar21 = *param_1 >> 1;
  pfVar13 = (float *)(param_1[2] + *param_1 * 4);
  iVar19 = iVar21 * 4 + iVar7 + -0x30;
  pfVar20 = local_24 + (iVar21 - iVar6);
  pfVar8 = (float *)(&stack0xffffffd8 + iVar7);
  do {
    pfVar16 = (float *)(&stack0xffffffd0 + *piVar18 * 4 + iVar19 + 0x30);
    pfVar9 = (float *)(&stack0xffffffd0 + piVar18[1] * 4 + iVar19 + 0x30);
    fVar3 = (*pfVar9 + *pfVar16) * *pfVar13 + (pfVar16[1] - pfVar9[1]) * pfVar13[1];
    fVar2 = (*pfVar9 + *pfVar16) * pfVar13[1] - (pfVar16[1] - pfVar9[1]) * *pfVar13;
    fVar4 = (pfVar9[1] + pfVar16[1]) * 0.5;
    fVar5 = (*pfVar16 - *pfVar9) * 0.5;
    pfVar8[-2] = fVar3 + fVar4;
    pfVar20[-5] = fVar4 - fVar3;
    pfVar8[-1] = fVar2 + fVar5;
    pfVar20[-4] = fVar2 - fVar5;
    pfVar16 = (float *)(&stack0xffffffd0 + piVar18[2] * 4 + iVar19 + 0x30);
    pfVar9 = (float *)(&stack0xffffffd0 + piVar18[3] * 4 + iVar19 + 0x30);
    fVar3 = (pfVar16[1] - pfVar9[1]) * pfVar13[3] + (*pfVar9 + *pfVar16) * pfVar13[2];
    fVar2 = (*pfVar9 + *pfVar16) * pfVar13[3] - (pfVar16[1] - pfVar9[1]) * pfVar13[2];
    fVar4 = (pfVar9[1] + pfVar16[1]) * 0.5;
    fVar5 = (*pfVar16 - *pfVar9) * 0.5;
    *pfVar8 = fVar3 + fVar4;
    pfVar16 = pfVar20 + -7;
    pfVar13 = pfVar13 + 4;
    piVar18 = piVar18 + 4;
    pfVar9 = pfVar8 + 2;
    pfVar20[-7] = fVar4 - fVar3;
    pfVar8[1] = fVar2 + fVar5;
    pfVar20[-6] = fVar2 - fVar5;
    pfVar20 = pfVar20 + -4;
    pfVar8 = pfVar8 + 4;
  } while (pfVar9 < pfVar16);
  pfVar20 = (float *)(iVar1 + param_1[2]);
  pfVar13 = param_3 + iVar17;
  if (0 < iVar14) {
    do {
      pfVar13 = pfVar13 + -1;
      iVar14 = iVar14 + -1;
      *param_3 = (pfVar20[1] * pfVar12[1] + *pfVar20 * *pfVar12) * (float)param_1[4];
      *pfVar13 = (pfVar20[1] * *pfVar12 - *pfVar20 * pfVar12[1]) * (float)param_1[4];
      pfVar20 = pfVar20 + 2;
      pfVar12 = pfVar12 + 2;
      param_3 = param_3 + 1;
    } while (iVar14 != 0);
  }
  return;
}

