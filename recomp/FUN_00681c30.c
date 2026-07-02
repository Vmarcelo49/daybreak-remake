// ============================================
// Address:  0x00681c30
// Original: FUN_00681c30
// Status:   unreviewed
// ============================================


void FUN_00681c30(undefined4 *param_1,int param_2,int param_3,uint param_4,int param_5,uint param_6)

{
  float fVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  
  param_4 = -(uint)(param_5 != 0) & param_4;
  param_6 = -(uint)(param_5 != 0) & param_6;
  pfVar5 = (float *)(&PTR_DAT_006c67c4)[*(int *)(param_2 + param_4 * 4)];
  puVar2 = (&PTR_DAT_006c67c4)[*(int *)(param_2 + param_6 * 4)];
  iVar9 = *(int *)(param_3 + param_5 * 4);
  iVar8 = *(int *)(param_3 + param_4 * 4);
  iVar3 = *(int *)(param_3 + param_6 * 4);
  iVar6 = (int)(iVar9 + (iVar9 >> 0x1f & 3U)) >> 2;
  iVar11 = iVar6 - ((int)(iVar8 + (iVar8 >> 0x1f & 3U)) >> 2);
  iVar6 = (iVar9 / 2 - ((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2)) + iVar6;
  iVar12 = iVar8 / 2 + iVar11;
  iVar8 = iVar3 / 2 + iVar6;
  iVar4 = 0;
  iVar7 = iVar11;
  puVar13 = param_1;
  if (0 < iVar11) {
    for (; iVar4 = iVar11, iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar13 = 0;
      puVar13 = puVar13 + 1;
    }
  }
  if (iVar4 < iVar12) {
    iVar12 = iVar12 - iVar4;
    pfVar10 = (float *)(param_1 + iVar4);
    do {
      fVar1 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      iVar12 = iVar12 + -1;
      *pfVar10 = *pfVar10 * fVar1;
      pfVar10 = pfVar10 + 1;
    } while (iVar12 != 0);
  }
  if (iVar6 < iVar8) {
    iVar8 = iVar8 - iVar6;
    pfVar5 = (float *)(param_1 + iVar6);
    pfVar10 = (float *)(puVar2 + (iVar3 / 2) * 4 + -4);
    iVar6 = iVar6 + iVar8;
    do {
      fVar1 = *pfVar10;
      pfVar10 = pfVar10 + -1;
      iVar8 = iVar8 + -1;
      *pfVar5 = fVar1 * *pfVar5;
      pfVar5 = pfVar5 + 1;
    } while (iVar8 != 0);
  }
  if (iVar6 < iVar9) {
    puVar13 = param_1 + iVar6;
    for (iVar9 = iVar9 - iVar6; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar13 = 0;
      puVar13 = puVar13 + 1;
    }
  }
  return;
}

