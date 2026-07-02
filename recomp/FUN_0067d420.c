// ============================================
// Address:  0x0067d420
// Original: FUN_0067d420
// Status:   unreviewed
// ============================================


void FUN_0067d420(int *param_1,int param_2,float *param_3,int param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float10 fVar12;
  float local_2c;
  int local_28;
  int local_24;
  int local_18;
  
  iVar3 = param_1[1];
  iVar11 = *param_1;
  iVar4 = *(int *)(iVar3 + 0x200);
  local_24 = 0;
  iVar5 = *(int *)(iVar3 + 0x1fc);
  if (iVar11 < *(int *)(iVar3 + 0x1fc)) {
    iVar5 = iVar11;
  }
  iVar6 = 0;
  if (*(int *)(iVar3 + 500) != 0) {
    if (0 < iVar5) {
      pfVar8 = param_3;
      local_18 = iVar5;
      do {
        fVar12 = (float10)FUN_0069a090((double)(*(float *)((param_2 - (int)param_3) + (int)pfVar8) +
                                               0.5));
        *pfVar8 = (float)fVar12;
        pfVar8 = pfVar8 + 1;
        local_18 = local_18 + -1;
        local_24 = iVar5;
      } while (local_18 != 0);
    }
    iVar9 = iVar4 + local_24;
    iVar6 = local_24;
    if (iVar9 <= iVar11) {
      iVar10 = local_24 * 4;
      do {
        fVar2 = 0.0;
        local_2c = 0.0;
        if (local_24 < iVar9) {
          pfVar8 = (float *)(iVar10 + param_2);
          iVar6 = iVar9 - local_24;
          do {
            fVar1 = *pfVar8;
            pfVar8 = pfVar8 + 1;
            iVar6 = iVar6 + -1;
            fVar2 = fVar1 * fVar1 + fVar2;
            local_2c = fVar2;
          } while (iVar6 != 0);
        }
        local_28 = 0;
        if (0 < iVar4) {
          local_18 = 0;
          do {
            iVar6 = *(int *)(local_18 + iVar5 * -4 + iVar10 + param_4);
            fVar2 = *(float *)(param_2 + iVar6 * 4);
            if (fVar2 * fVar2 < 0.25) {
              if (local_2c < (float)*(double *)(iVar3 + 0x208)) {
                if (local_28 < iVar4) {
                  iVar6 = local_28 * 4;
                  local_28 = iVar4 - local_28;
                  do {
                    iVar7 = iVar6 + iVar5 * -4;
                    iVar6 = iVar6 + 4;
                    local_28 = local_28 + -1;
                    param_3[*(int *)(iVar7 + iVar10 + param_4)] = 0.0;
                  } while (local_28 != 0);
                }
                break;
              }
              fVar12 = (float10)FUN_0067d670();
              param_3[iVar6] = (float)fVar12;
              local_2c = local_2c - 1.0;
            }
            else {
              fVar12 = (float10)FUN_0069a090((double)(*(float *)(param_2 + iVar6 * 4) + 0.5));
              param_3[iVar6] = (float)fVar12;
              fVar2 = *(float *)(param_2 + iVar6 * 4);
              local_2c = local_2c - fVar2 * fVar2;
            }
            local_28 = local_28 + 1;
            local_18 = local_18 + 4;
          } while (local_28 < iVar4);
        }
        iVar9 = iVar9 + iVar4;
        iVar10 = iVar10 + iVar4 * 4;
        iVar6 = local_24 + iVar4;
        local_24 = iVar6;
      } while (iVar9 <= iVar11);
    }
  }
  if (iVar6 < iVar11) {
    iVar11 = iVar11 - iVar6;
    pfVar8 = param_3 + iVar6;
    do {
      fVar12 = (float10)FUN_0069a090((double)(*(float *)((int)pfVar8 + (param_2 - (int)param_3)) +
                                             0.5));
      *pfVar8 = (float)fVar12;
      pfVar8 = pfVar8 + 1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  return;
}

