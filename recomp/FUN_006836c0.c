// ============================================
// Address:  0x006836c0
// Original: FUN_006836c0
// Status:   unreviewed
// ============================================


int FUN_006836c0(int *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int local_14;
  float local_c;
  
  iVar7 = *param_1;
  piVar3 = *(int **)(param_1[3] + 0x28);
  local_14 = 0;
  if (0 < iVar7) {
    iVar9 = *piVar3;
    iVar5 = piVar3[3] >> 1;
    pfVar4 = param_2 + iVar7;
    local_c = (float)iVar7;
    do {
      fVar1 = pfVar4[-1];
      pfVar4 = pfVar4 + -1;
      if (*(float *)(iVar9 + iVar5 * 4) <= fVar1) {
        iVar6 = iVar5 + 1;
        if (iVar6 < piVar3[3] + -1) {
          pfVar8 = (float *)(iVar9 + iVar6 * 4);
          do {
            if (fVar1 < *pfVar8) break;
            iVar6 = iVar6 + 1;
            pfVar8 = pfVar8 + 1;
          } while (iVar6 < piVar3[3] + -1);
        }
      }
      else {
        iVar6 = iVar5;
        if ((fVar1 < *(float *)(iVar9 + -4 + iVar5 * 4)) && (iVar6 = iVar5 + -1, 0 < iVar6)) {
          pfVar8 = (float *)(iVar9 + -4 + iVar6 * 4);
          do {
            if (*pfVar8 <= fVar1) break;
            iVar6 = iVar6 + -1;
            pfVar8 = pfVar8 + -1;
          } while (0 < iVar6);
        }
      }
      local_14 = *(int *)(piVar3[1] + iVar6 * 4) + piVar3[2] * local_14;
      local_c = (float)((int)local_c + -1);
    } while (local_c != 0.0);
  }
  piVar3 = *(int **)(param_1[3] + 8);
  if (piVar3[local_14] < 1) {
    iVar9 = param_1[4];
    iVar5 = 0;
    local_c = 0.0;
    local_14 = -1;
    if (0 < param_1[1]) {
      do {
        iVar6 = local_14;
        fVar1 = local_c;
        if (0 < *piVar3) {
          fVar1 = 0.0;
          if (0 < iVar7) {
            pfVar4 = param_2;
            iVar6 = iVar7;
            do {
              fVar2 = *(float *)((iVar9 - (int)param_2) + (int)pfVar4) - *pfVar4;
              pfVar4 = pfVar4 + 1;
              iVar6 = iVar6 + -1;
              fVar1 = fVar2 * fVar2 + fVar1;
            } while (iVar6 != 0);
          }
          iVar6 = iVar5;
          if ((local_14 != -1) && (local_c <= fVar1)) {
            iVar6 = local_14;
            fVar1 = local_c;
          }
        }
        local_c = fVar1;
        local_14 = iVar6;
        iVar5 = iVar5 + 1;
        piVar3 = piVar3 + 1;
        iVar9 = iVar9 + iVar7 * 4;
      } while (iVar5 < param_1[1]);
    }
  }
  pfVar4 = (float *)(param_1[4] + local_14 * iVar7 * 4);
  if (iVar7 < 1) {
    return local_14;
  }
  do {
    iVar7 = iVar7 + -1;
    *param_2 = *param_2 - *pfVar4;
    pfVar4 = pfVar4 + 1;
    param_2 = param_2 + 1;
  } while (iVar7 != 0);
  return local_14;
}

