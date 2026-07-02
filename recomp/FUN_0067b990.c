// ============================================
// Address:  0x0067b990
// Original: FUN_0067b990
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * FUN_0067b990(float *param_1,float param_2,int param_3,float *param_4,float *param_5)

{
  int iVar1;
  int iVar2;
  float fVar3;
  void *pvVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  undefined4 extraout_ECX;
  int iVar10;
  uint uVar11;
  undefined1 *puVar12;
  undefined4 *puVar13;
  float10 fVar14;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 fVar15;
  undefined4 auStack_7f2c [3];
  undefined8 uStack_7f20;
  float local_7f0c [55];
  float afStack_7e30 [7561];
  float local_80c [56];
  undefined1 local_72c [1568];
  float local_10c [56];
  float *local_2c;
  undefined8 local_28;
  int local_20;
  undefined4 *local_1c;
  float *local_18;
  float *local_14;
  float *local_10;
  void *local_c;
  float *local_8;
  
  local_8 = (float *)0x67b99d;
  uStack_7f20._4_4_ = 0x67b9b0;
  iVar2 = param_3 * -4;
  local_1c = local_7f0c + (-3 - param_3);
  *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x44;
  *(undefined4 *)((int)&uStack_7f20 + iVar2) = 0x67b9ba;
  local_c = _malloc(*(size_t *)((int)&uStack_7f20 + iVar2 + 4));
  pfVar5 = local_7f0c;
  for (iVar7 = 0x1dc0; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar5 = 0.0;
    pfVar5 = pfVar5 + 1;
  }
  local_8 = local_7f0c;
  local_10 = param_1;
  local_14 = (float *)&DAT_006b89f8;
  local_18 = (float *)&DAT_006b8898;
  do {
    pfVar5 = local_10c;
    iVar7 = 0x38;
    pfVar9 = local_18;
    do {
      fVar3 = 999.0;
      iVar10 = 4;
      pfVar8 = pfVar9;
      do {
        if ((int)pfVar8 < 0x6b89f8) {
          if (*pfVar8 < fVar3) {
            fVar3 = *pfVar8;
          }
        }
        else if (_DAT_006b89f4 < fVar3) {
          fVar3 = _DAT_006b89f4;
        }
        pfVar8 = pfVar8 + 1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
      *pfVar5 = fVar3;
      pfVar9 = pfVar9 + 1;
      pfVar5 = pfVar5 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    pfVar5 = local_14;
    pfVar9 = local_8 + 0x70;
    for (iVar7 = 0x150; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
    pfVar5 = local_14;
    pfVar9 = local_8;
    for (iVar7 = 0x38; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
    local_2c = local_8 + 0x38;
    pfVar5 = local_14;
    pfVar9 = local_2c;
    for (iVar7 = 0x38; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar9 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar9 = pfVar9 + 1;
    }
    iVar7 = 8;
    pfVar5 = local_8;
    do {
      uVar11 = 0x10;
      pfVar9 = pfVar5;
      do {
        fVar3 = (float)(int)((uVar11 ^ (int)uVar11 >> 0x1f) - ((int)uVar11 >> 0x1f)) *
                (float)param_5 + (float)param_4;
        if ((fVar3 < 0.0) && (0.0 < (float)param_4)) {
          fVar3 = 0.0;
        }
        if ((0.0 < fVar3) && ((float)param_4 < 0.0)) {
          fVar3 = 0.0;
        }
        pfVar5 = pfVar9 + 1;
        uVar11 = uVar11 - 1;
        *pfVar9 = fVar3 + *pfVar9;
        pfVar9 = pfVar5;
      } while (-0x28 < (int)uVar11);
      iVar7 = iVar7 + -1;
      local_28 = (double)CONCAT44(pfVar5,(undefined4)local_28);
    } while (iVar7 != 0);
    param_1 = (float *)0x0;
    pfVar5 = local_80c;
    do {
      local_20 = 2;
      if (1 < (int)param_1) {
        local_20 = (int)param_1;
      }
      *(float **)((int)&uStack_7f20 + iVar2 + 4) = local_10;
      *(float *)((int)&uStack_7f20 + iVar2 + 4) =
           ((*local_10 + 100.0) - (float)local_20 * 10.0) - 30.0;
      *(float **)((int)&uStack_7f20 + iVar2) = local_8;
      auStack_7f2c[2 - param_3] = 0x67bb41;
      FUN_0067c170();
      pfVar9 = local_10c;
      pfVar8 = pfVar5;
      for (iVar7 = 0x38; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar8 = *pfVar9;
        pfVar9 = pfVar9 + 1;
        pfVar8 = pfVar8 + 1;
      }
      *(float *)((int)&uStack_7f20 + iVar2 + 4) = (100.0 - (float)(int)param_1 * 10.0) - 30.0;
      *(float **)((int)&uStack_7f20 + iVar2) = pfVar5;
      auStack_7f2c[2 - param_3] = 0x67bb71;
      FUN_0067c170();
      pfVar9 = local_8;
      auStack_7f2c[2 - param_3] = local_8;
      auStack_7f2c[1 - param_3] = pfVar5;
      auStack_7f2c[-param_3] = 0x67bb7b;
      FUN_0067c140();
      param_1 = (float *)((int)param_1 + 1);
      local_8 = pfVar9 + 0x38;
      pfVar5 = pfVar5 + 0x38;
    } while ((int)param_1 < 8);
    puVar12 = local_72c;
    iVar7 = 7;
    pfVar5 = local_2c;
    do {
      *(undefined1 **)((int)&uStack_7f20 + iVar2 + 4) = puVar12 + -0xe0;
      *(undefined1 **)((int)&uStack_7f20 + iVar2) = puVar12;
      auStack_7f2c[2 - param_3] = 0x67bbb8;
      FUN_0067c110();
      auStack_7f2c[2 - param_3] = puVar12;
      auStack_7f2c[1 - param_3] = pfVar5;
      auStack_7f2c[-param_3] = 0x67bbbf;
      FUN_0067c110();
      puVar12 = puVar12 + 0xe0;
      pfVar5 = pfVar5 + 0x38;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    local_18 = local_18 + 4;
    local_14 = local_14 + 0x150;
    local_10 = local_10 + 1;
    local_8 = local_28._4_4_;
  } while ((int)local_18 < 0x6b89a8);
  param_4 = (float *)0x0;
  do {
    *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x20;
    *(undefined4 *)((int)&uStack_7f20 + iVar2) = 0x67bc0e;
    pvVar4 = _malloc(*(size_t *)((int)&uStack_7f20 + iVar2 + 4));
    *(undefined4 *)((int)&uStack_7f20 + iVar2) = extraout_ECX;
    *(void **)((int)local_c + (int)param_4 * 4) = pvVar4;
    local_28 = (double)((float10)(int)param_4 * (float10)0.5);
    fVar15 = (float10)1.4426950408889634 *
             ((float10)(int)param_4 * (float10)0.5 + (float10)5.965784072875977) *
             (float10)0.6931470036506653;
    fVar14 = ROUND(fVar15);
    fVar15 = (float10)f2xm1(fVar15 - fVar14);
    fVar14 = (float10)fscale((float10)1 + fVar15,fVar14);
    *(double *)((int)&uStack_7f20 + iVar2) = (double)(fVar14 / (float10)param_2);
    auStack_7f2c[2 - param_3] = 0x67bc51;
    FUN_0069a090();
    auStack_7f2c[2 - param_3] = 0x67bc56;
    iVar7 = __ftol();
    fVar14 = (float10)log2((float10)iVar7 * (float10)param_2 + (float10)1.0);
    fVar14 = (float10)0.6931471805599453 * fVar14 * (float10)1.4426950216293335 -
             (float10)5.965784072875977;
    *(double *)((int)&uStack_7f20 + iVar2) = (double)(fVar14 + fVar14);
    auStack_7f2c[2 - param_3] = 0x67bc83;
    FUN_0066d020();
    auStack_7f2c[2 - param_3] = 0x67bc88;
    pfVar5 = (float *)__ftol();
    fVar14 = (float10)log2((float10)(iVar7 + 1) * (float10)param_2);
    fVar14 = (float10)0.6931471805599453 * fVar14 * (float10)1.4426950216293335 -
             (float10)5.965784072875977;
    *(double *)((int)&uStack_7f20 + iVar2) = (double)(fVar14 + fVar14);
    auStack_7f2c[2 - param_3] = 0x67bcb3;
    local_10 = pfVar5;
    FUN_0069a090();
    *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x67bcbb;
    local_8 = (float *)__ftol();
    if ((int)param_4 < (int)pfVar5) {
      local_10 = param_4;
      pfVar5 = param_4;
    }
    if ((int)pfVar5 < 0) {
      local_10 = (float *)0x0;
    }
    if (0x10 < (int)local_8) {
      local_8 = (float *)0x10;
    }
    local_20 = 0;
    do {
      iVar7 = local_20;
      *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0xe8;
      *(undefined4 *)((int)&uStack_7f20 + iVar2) = 0x67bce9;
      pvVar4 = _malloc(*(size_t *)((int)&uStack_7f20 + iVar2 + 4));
      *(void **)(*(int *)((int)local_c + (int)param_4 * 4) + iVar7 * 4) = pvVar4;
      iVar10 = param_3;
      puVar13 = local_1c;
      if (0 < param_3) {
        for (; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = 0x4479c000;
          puVar13 = puVar13 + 1;
        }
      }
      param_5 = local_10;
      if ((int)local_10 <= (int)local_8) {
        iVar7 = iVar7 + (int)local_10 * 8;
        local_18 = (float *)(iVar7 * 0x38);
        local_14 = afStack_7e30 + iVar7 * 0x38;
        do {
          iVar7 = 0;
          param_1 = (float *)0x0;
          fVar14 = (float10)(int)param_5 * (float10)0.5;
          do {
            fVar15 = (float10)1.4426950408889634 *
                     ((((float10)(int)param_1 * (float10)0.125 + fVar14) - (float10)2.0625) +
                     (float10)5.965784072875977) * (float10)0.6931470036506653;
            fVar14 = ROUND(fVar15);
            fVar15 = (float10)f2xm1(fVar15 - fVar14);
            fscale((float10)1 + fVar15,fVar14);
            *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x67bd8d;
            iVar6 = __ftol();
            fVar15 = (float10)1.4426950408889634 *
                     ((extraout_ST0 - (float10)1.9375) + (float10)5.965784072875977) *
                     (float10)0.6931470036506653;
            fVar14 = ROUND(fVar15);
            fVar15 = (float10)f2xm1(fVar15 - fVar14);
            fscale((float10)1 + fVar15,fVar14);
            *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x67bdc5;
            iVar10 = __ftol();
            if (iVar6 < 0) {
              iVar6 = 0;
            }
            if (param_3 < iVar6) {
              iVar6 = param_3;
            }
            if (iVar6 < iVar7) {
              iVar7 = iVar6;
            }
            if (iVar10 < 0) {
              iVar10 = 0;
            }
            if (param_3 < iVar10) {
              iVar10 = param_3;
            }
            if (iVar7 < iVar10) {
              pfVar5 = (float *)(local_1c + iVar7);
              do {
                if (param_3 <= iVar7) break;
                if (local_7f0c[(int)local_18 + (int)param_1] < *pfVar5) {
                  *pfVar5 = local_7f0c[(int)local_18 + (int)param_1];
                }
                iVar7 = iVar7 + 1;
                pfVar5 = pfVar5 + 1;
              } while (iVar7 < iVar10);
            }
            param_1 = (float *)((int)param_1 + 1);
            fVar14 = extraout_ST0_00;
          } while ((int)param_1 < 0x38);
          if (iVar7 < param_3) {
            iVar10 = param_3 - iVar7;
            pfVar5 = (float *)(local_1c + iVar7);
            do {
              if (*local_14 < *pfVar5) {
                *pfVar5 = *local_14;
              }
              pfVar5 = pfVar5 + 1;
              iVar10 = iVar10 + -1;
            } while (iVar10 != 0);
          }
          param_5 = (float *)((int)param_5 + 1);
          local_18 = local_18 + 0x70;
          local_14 = local_14 + 0x1c0;
          iVar7 = local_20;
        } while ((int)param_5 <= (int)local_8);
      }
      if ((int)param_4 + 1 < 0x11) {
        iVar10 = 0;
        param_1 = (float *)0x0;
        do {
          fVar15 = (float10)1.4426950408889634 *
                   ((((float10)(int)param_1 * (float10)0.125 + (float10)local_28) - (float10)2.0625)
                   + (float10)5.965784072875977) * (float10)0.6931470036506653;
          fVar14 = ROUND(fVar15);
          fVar15 = (float10)f2xm1(fVar15 - fVar14);
          fscale((float10)1 + fVar15,fVar14);
          *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x67bed9;
          iVar6 = __ftol();
          fVar15 = (float10)1.4426950408889634 *
                   ((extraout_ST0_01 - (float10)1.9375) + (float10)5.965784072875977) *
                   (float10)0.6931470036506653;
          fVar14 = ROUND(fVar15);
          fVar15 = (float10)f2xm1(fVar15 - fVar14);
          fscale((float10)1 + fVar15,fVar14);
          *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x67bf11;
          param_5 = (float *)__ftol();
          if (iVar6 < 0) {
            iVar6 = 0;
          }
          if (param_3 < iVar6) {
            iVar6 = param_3;
          }
          if (iVar6 < iVar10) {
            iVar10 = iVar6;
          }
          if ((int)param_5 < 0) {
            param_5 = (float *)0x0;
          }
          if (param_3 < (int)param_5) {
            param_5 = (float *)param_3;
          }
          if (iVar10 < (int)param_5) {
            pfVar5 = (float *)(local_1c + iVar10);
            do {
              if (param_3 <= iVar10) break;
              iVar6 = (int)param_1 + (iVar7 + ((int)param_4 + 1) * 8) * 0x38;
              if (local_7f0c[iVar6] < *pfVar5) {
                *pfVar5 = local_7f0c[iVar6];
              }
              iVar10 = iVar10 + 1;
              pfVar5 = pfVar5 + 1;
            } while (iVar10 < (int)param_5);
          }
          param_1 = (float *)((int)param_1 + 1);
        } while ((int)param_1 < 0x38);
        if (iVar10 < param_3) {
          iVar6 = param_3 - iVar10;
          pfVar5 = (float *)(local_1c + iVar10);
          do {
            if (afStack_7e30[(iVar7 + ((int)param_4 + 1) * 8) * 0x38] < *pfVar5) {
              *pfVar5 = afStack_7e30[(iVar7 + ((int)param_4 + 1) * 8) * 0x38];
            }
            pfVar5 = pfVar5 + 1;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
        }
      }
      param_1 = (float *)0x0;
      iVar10 = 8;
      do {
        fVar15 = (float10)1.4426950408889634 *
                 ((((float10)(int)param_1 * (float10)0.125 + (float10)local_28) - (float10)2.0) +
                 (float10)5.965784072875977) * (float10)0.6931470036506653;
        fVar14 = ROUND(fVar15);
        fVar15 = (float10)f2xm1(fVar15 - fVar14);
        fscale((float10)1 + fVar15,fVar14);
        *(undefined4 *)((int)&uStack_7f20 + iVar2 + 4) = 0x67c026;
        iVar6 = __ftol();
        if (iVar6 < 0) {
          *(undefined4 *)(*(int *)(*(int *)((int)local_c + (int)param_4 * 4) + iVar7 * 4) + iVar10)
               = 0xc479c000;
        }
        else {
          iVar1 = *(int *)((int)local_c + (int)param_4 * 4);
          if (iVar6 < param_3) {
            *(undefined4 *)(*(int *)(iVar1 + iVar7 * 4) + iVar10) = local_1c[iVar6];
          }
          else {
            *(undefined4 *)(*(int *)(iVar1 + iVar7 * 4) + iVar10) = 0xc479c000;
          }
        }
        iVar10 = iVar10 + 4;
        param_1 = (float *)((int)param_1 + 1);
      } while (iVar10 < 0xe8);
      iVar10 = 0;
      pfVar9 = *(float **)(*(int *)((int)local_c + (int)param_4 * 4) + iVar7 * 4);
      pfVar5 = pfVar9 + 2;
      do {
        if (-200.0 < *pfVar5) break;
        iVar10 = iVar10 + 1;
        pfVar5 = pfVar5 + 1;
      } while (iVar10 < 0x10);
      iVar6 = 0x37;
      *pfVar9 = (float)iVar10;
      iVar10 = *(int *)(*(int *)((int)local_c + (int)param_4 * 4) + iVar7 * 4);
      pfVar5 = (float *)(iVar10 + 0xe4);
      do {
        if (-200.0 < *pfVar5) break;
        iVar6 = iVar6 + -1;
        pfVar5 = pfVar5 + -1;
      } while (0x11 < iVar6);
      local_20 = iVar7 + 1;
      *(float *)(iVar10 + 4) = (float)iVar6;
    } while (iVar7 + 1 < 8);
    param_4 = (float *)((int)param_4 + 1);
    if (0x10 < (int)param_4) {
      return local_c;
    }
  } while( true );
}

