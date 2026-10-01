// Function: FUN_006809c0
// Address:  0x006809c0
// Source:   batch_decompile (mass dump)
// Hash:     5394d2e4b2c28958


void FUN_006809c0(int *param_1,int param_2)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  byte bVar5;
  float *pfVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  float10 fVar13;
  float10 fVar14;
  int local_10;
  int local_c;
  
  iVar10 = (int)(param_2 + (param_2 >> 0x1f & 3U)) >> 2;
  piVar1 = _malloc(iVar10 * 4);
  pfVar2 = _malloc((iVar10 + param_2) * 4);
  fVar13 = (float10)log2((float10)param_2);
  fVar14 = (float10)log2((float10)2.0);
  FUN_0069a090((double)(((float10)0.6931471805599453 * fVar13) /
                        ((float10)0.6931471805599453 * fVar14) + (float10)0.5));
  iVar3 = __ftol();
  param_1[1] = iVar3;
  *param_1 = param_2;
  param_1[2] = (int)pfVar2;
  param_1[3] = (int)piVar1;
  if (0 < iVar10) {
    local_10 = 0;
    local_c = 1;
    pfVar4 = pfVar2;
    pfVar6 = pfVar2 + (param_2 >> 1);
    do {
      fVar13 = (float10)local_10;
      local_10 = local_10 + 4;
      fVar13 = fVar13 * ((float10)3.1415927 / (float10)param_2);
      iVar10 = iVar10 + -1;
      fVar14 = (float10)fcos(fVar13);
      *pfVar4 = (float)fVar14;
      fVar13 = (float10)fsin(fVar13);
      pfVar4[1] = (float)-fVar13;
      fVar13 = (float10)local_c * ((float10)3.1415927 / (float10)(param_2 * 2));
      fVar14 = (float10)fcos(fVar13);
      *pfVar6 = (float)fVar14;
      fVar13 = (float10)fsin(fVar13);
      pfVar6[1] = (float)fVar13;
      pfVar4 = pfVar4 + 2;
      pfVar6 = pfVar6 + 2;
      local_c = local_c + 2;
    } while (iVar10 != 0);
  }
  iVar10 = (int)((param_2 >> 0x1f & 7U) + param_2) >> 3;
  if (0 < iVar10) {
    local_c = 2;
    iVar7 = iVar10;
    pfVar2 = pfVar2 + param_2;
    do {
      fVar13 = (float10)local_c;
      local_c = local_c + 4;
      iVar7 = iVar7 + -1;
      fVar13 = fVar13 * ((float10)3.1415927 / (float10)param_2);
      fVar14 = (float10)fcos(fVar13);
      *pfVar2 = (float)(fVar14 * (float10)0.5);
      fVar13 = (float10)fsin(fVar13);
      pfVar2[1] = (float)(fVar13 * (float10)-0.5);
      pfVar2 = pfVar2 + 2;
    } while (iVar7 != 0);
  }
  uVar9 = 0;
  uVar11 = 1 << ((char)iVar3 - 2U & 0x1f);
  if (0 < iVar10) {
    do {
      uVar12 = 0;
      bVar5 = 0;
      uVar8 = uVar11;
      while (uVar8 != 0) {
        if ((uVar9 & uVar8) != 0) {
          uVar12 = uVar12 | 1 << (bVar5 & 0x1f);
        }
        bVar5 = bVar5 + 1;
        uVar8 = (int)uVar11 >> (bVar5 & 0x1f);
      }
      uVar9 = uVar9 + 1;
      *piVar1 = (~uVar12 & (1 << ((char)iVar3 - 1U & 0x1f)) - 1U) - 1;
      piVar1[1] = uVar12;
      piVar1 = piVar1 + 2;
    } while ((int)uVar9 < iVar10);
  }
  param_1[4] = (int)(4.0 / (float)param_2);
  return;
}

