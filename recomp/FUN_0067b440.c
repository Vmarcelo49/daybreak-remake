// ============================================
// Address:  0x0067b440
// Original: FUN_0067b440
// Status:   unreviewed
// ============================================


void FUN_0067b440(int *param_1,int param_2,float *param_3,int param_4,int param_5)

{
  float *pfVar1;
  size_t _Size;
  float *pfVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  void *pvVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  float10 fVar16;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float10 fVar17;
  float10 extraout_ST1_00;
  int local_24;
  int local_20;
  
  iVar7 = param_5;
  iVar6 = param_4;
  piVar5 = param_1;
  piVar15 = param_1;
  for (iVar12 = 0xc; iVar12 != 0; iVar12 = iVar12 + -1) {
    *piVar15 = 0;
    piVar15 = piVar15 + 1;
  }
  local_24 = -99;
  iVar14 = 1;
  param_1[9] = (int)*param_3;
  fVar16 = (float10)log2((float10)(int)*param_3 * (float10)8.0);
  fVar17 = (float10)log2((float10)2.0);
  FUN_0069a090((double)(((float10)0.6931471805599453 * fVar16) /
                        ((float10)0.6931471805599453 * fVar17) + (float10)0.5));
  iVar12 = __ftol();
  fVar16 = (float10)param_4;
  param_1[8] = iVar12;
  log2(((float10)param_5 * (float10)0.25 * (float10)0.5) / fVar16);
  iVar12 = __ftol();
  param_1[7] = iVar12;
  log2((((float10)param_4 + (float10)0.25) * fVar16 * (float10)0.5) / extraout_ST1);
  iVar8 = __ftol();
  _Size = param_4 * 4;
  param_1[10] = (iVar8 - iVar12) + 1;
  pvVar9 = _malloc(_Size);
  param_1[4] = (int)pvVar9;
  pvVar9 = _malloc(_Size);
  param_1[5] = (int)pvVar9;
  pvVar9 = _malloc(_Size);
  param_1[6] = (int)pvVar9;
  param_1[1] = param_2;
  iVar12 = 0;
  *param_1 = param_4;
  param_1[0xb] = param_5;
  iVar8 = 0;
  param_3 = (float *)&DAT_006b889c;
  do {
    iVar12 = iVar12 + 1;
    fVar17 = (float10)1.4426950408889634 *
             (((float10)iVar12 * (float10)0.125 - (float10)2.0) + (float10)5.965784072875977) *
             (float10)0.6931470036506653;
    fVar16 = ROUND(fVar17);
    fVar17 = (float10)f2xm1(fVar17 - fVar16);
    fVar16 = (float10)fscale((float10)1 + fVar17,fVar16);
    FUN_0069a090((double)((fVar16 * (float10)param_4 + fVar16 * (float10)param_4) / (float10)param_5
                         + (float10)0.5));
    iVar10 = __ftol();
    fVar3 = param_3[-1];
    if (iVar8 < iVar10) {
      iVar13 = iVar10 - iVar8;
      fVar4 = *param_3 - fVar3;
      do {
        if (param_4 <= iVar8) break;
        iVar8 = iVar8 + 1;
        *(float *)(param_1[4] + -4 + iVar8 * 4) = fVar3 + 100.0;
        fVar3 = fVar3 + fVar4 / (float)iVar13;
      } while (iVar8 < iVar10);
    }
    param_3 = param_3 + 1;
  } while ((int)param_3 < 0x6b89f8);
  iVar12 = 0;
  if (0 < param_4) {
    iVar8 = param_5 / (param_4 * 2);
    param_3 = (float *)0x0;
    param_1 = (int *)0x0;
    iVar10 = iVar8 * iVar8;
    do {
      local_20 = *(int *)(param_2 + 0x78) + local_24;
      fVar16 = (float10)fpatan((float10)((int)param_1 * iVar12) * (float10)1.85e-08,(float10)1);
      fVar17 = (float10)fpatan((float10)(int)param_3 * (float10)0.00074,(float10)1);
      fVar3 = (float)((float10)(int)param_3 * (float10)0.0001 +
                     fVar17 * (float10)13.100000381469727 + fVar16 * (float10)2.240000009536743);
      if (local_20 < iVar12) {
        param_5 = iVar8 * local_24;
        iVar13 = iVar10 * local_24;
        do {
          fVar16 = (float10)fpatan((float10)(iVar13 * local_24) * (float10)1.85e-08,(float10)1);
          fVar17 = (float10)fpatan((float10)param_5 * (float10)0.00074,(float10)1);
          if ((float10)(fVar3 - *(float *)(param_2 + 0x70)) <=
              (float10)param_5 * (float10)0.0001 +
              fVar17 * (float10)13.100000381469727 + fVar16 * (float10)2.240000009536743) break;
          iVar13 = iVar13 + iVar10;
          local_24 = local_24 + 1;
          param_5 = param_5 + iVar8;
          local_20 = local_20 + 1;
        } while (local_20 < iVar12);
      }
      if (iVar14 <= param_4) {
        param_5 = iVar8 * iVar14;
        iVar13 = iVar10 * iVar14;
        do {
          if (*(int *)(param_2 + 0x7c) + iVar12 <= iVar14) {
            fVar16 = (float10)fpatan((float10)(iVar13 * iVar14) * (float10)1.85e-08,(float10)1);
            fVar17 = (float10)fpatan((float10)param_5 * (float10)0.00074,(float10)1);
            if ((float10)fVar3 + (float10)*(float *)(param_2 + 0x74) <=
                (float10)param_5 * (float10)0.0001 +
                fVar17 * (float10)13.100000381469727 + fVar16 * (float10)2.240000009536743) break;
          }
          iVar14 = iVar14 + 1;
          param_5 = param_5 + iVar8;
          iVar13 = iVar13 + iVar10;
        } while (iVar14 <= param_4);
      }
      iVar12 = iVar12 + 1;
      *(int *)(piVar5[6] + -4 + iVar12 * 4) = local_24 * 0x10000 + -0x10001 + iVar14;
      param_1 = (int *)((int)param_1 + iVar10);
      param_3 = (float *)((int)param_3 + iVar8);
    } while (iVar12 < param_4);
  }
  param_4 = 0;
  if (0 < iVar6) {
    do {
      log2((((float10)param_4 + (float10)0.25) * (float10)iVar7 * (float10)0.5) / (float10)iVar6);
      uVar11 = __ftol();
      param_4 = param_4 + 1;
      *(undefined4 *)(piVar5[5] + -4 + param_4 * 4) = uVar11;
    } while (param_4 < iVar6);
  }
  iVar12 = FUN_0067b990(param_2 + 0x24,((float)iVar7 * 0.5) / (float)iVar6,iVar6,
                        *(undefined4 *)(param_2 + 0x18));
  piVar5[2] = iVar12;
  pvVar9 = _malloc(0xc);
  piVar5[3] = (int)pvVar9;
  iVar12 = 0;
  do {
    pvVar9 = _malloc(iVar6 * 4);
    iVar12 = iVar12 + 4;
    *(void **)(piVar5[3] + -4 + iVar12) = pvVar9;
  } while (iVar12 < 0xc);
  param_4 = 0;
  if (0 < iVar6) {
    fVar16 = (float10)iVar6 + (float10)iVar6;
    do {
      log2((((float10)param_4 + (float10)0.5) * (float10)iVar7) / fVar16);
      iVar8 = __ftol();
      iVar14 = 0;
      iVar12 = iVar8 * 4 + 0x88;
      do {
        iVar14 = iVar14 + 4;
        pfVar2 = (float *)(piVar5[1] + -4 + iVar12);
        pfVar1 = (float *)(piVar5[1] + iVar12);
        iVar12 = iVar12 + 0x44;
        *(float *)(*(int *)(piVar5[3] + -4 + iVar14) + param_4 * 4) =
             (float)((extraout_ST0 - (float10)iVar8) * (float10)*pfVar1 +
                    (float10)*pfVar2 * ((float10)1.0 - (extraout_ST0 - (float10)iVar8)));
      } while (iVar14 < 0xc);
      param_4 = param_4 + 1;
      fVar16 = extraout_ST1_00;
    } while (param_4 < iVar6);
  }
  return;
}

