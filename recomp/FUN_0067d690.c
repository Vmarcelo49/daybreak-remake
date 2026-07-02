// ============================================
// Address:  0x0067d690
// Original: FUN_0067d690
// Status:   unreviewed
// ============================================


void FUN_0067d690(int param_1,int param_2,int *param_3,int param_4,int param_5,int param_6,
                 int *param_7,int param_8,int param_9,int param_10)

{
  int iVar1;
  undefined4 *puVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  float *pfVar17;
  float10 fVar18;
  float local_6c;
  int *local_64;
  int local_60;
  int local_5c;
  int local_54;
  int local_3c;
  int local_34;
  int local_30;
  
  iVar6 = *param_3;
  local_30 = 0;
  if (0 < *(int *)(param_4 + 0x484)) {
    piVar13 = (int *)(param_4 + 0x888);
    local_64 = param_7;
    iVar15 = iVar6;
    do {
      iVar14 = piVar13[-0x100] * 4;
      if ((*(int *)(iVar14 + param_9) != 0) || (*(int *)(param_9 + *piVar13 * 4) != 0)) {
        iVar7 = *(int *)(iVar14 + param_5);
        iVar8 = *(int *)(*piVar13 * 4 + param_5);
        iVar1 = iVar7 + iVar6 * 4;
        iVar9 = *(int *)(iVar14 + param_8);
        iVar10 = *(int *)(*piVar13 * 4 + param_8);
        dVar4 = *(double *)(&DAT_006be338 + *(int *)(param_2 + 0xfc + param_1 * 4) * 8);
        dVar5 = *(double *)(&DAT_006be338 + *(int *)(param_2 + 0x138 + param_1 * 4) * 8);
        piVar11 = (int *)param_3[1];
        iVar16 = iVar15;
        if (piVar11[0x7e] != 0) {
          iVar16 = piVar11[0x80];
        }
        iVar12 = *(int *)(param_2 + 0x84 + (param_1 + *piVar11 * 0xf) * 4);
        *(undefined4 *)(iVar14 + param_9) = 1;
        *(undefined4 *)(param_9 + *piVar13 * 4) = 1;
        iVar15 = *param_3;
        local_34 = 0;
        if (0 < iVar15) {
          local_54 = 0;
          do {
            local_6c = 0.0;
            if (0 < iVar16) {
              pfVar17 = (float *)(local_54 + iVar8);
              iVar15 = iVar7 - iVar8;
              iVar14 = iVar1 - iVar8;
              local_60 = local_54;
              local_5c = local_34;
              local_3c = iVar16;
              do {
                if (local_5c < param_10) {
                  if ((((iVar12 <= local_5c) &&
                       (ABS(*(float *)(iVar15 + (int)pfVar17)) < (float)dVar5)) &&
                      (ABS(*pfVar17) < (float)dVar5)) ||
                     ((fVar3 = *(float *)(iVar15 + (int)pfVar17), ABS(fVar3) < (float)dVar4 &&
                      (ABS(*pfVar17) < (float)dVar4)))) {
                    puVar2 = (undefined4 *)((iVar9 - iVar8) + (int)pfVar17);
                    FUN_0067db50(*(undefined4 *)
                                  (*(int *)((int)local_64 + (param_6 - (int)param_7)) + local_60),
                                 *puVar2,*(undefined4 *)((int)puVar2 + (iVar10 - iVar9)),
                                 (float *)(iVar14 + (int)pfVar17),pfVar17 + iVar6);
                    fVar18 = (float10)FUN_0069a090();
                    if (fVar18 == (float10)0.0) {
                      fVar3 = *(float *)(iVar14 + (int)pfVar17);
                      local_6c = fVar3 * fVar3 + local_6c;
                    }
                  }
                  else {
                    FUN_0067da80(fVar3,*pfVar17,iVar14 + (int)pfVar17,pfVar17 + iVar6);
                  }
                }
                else {
                  *(undefined4 *)(iVar14 + (int)pfVar17) = 0;
                  pfVar17[iVar6] = 0.0;
                }
                local_60 = local_60 + 4;
                pfVar17 = pfVar17 + 1;
                local_5c = local_5c + 1;
                local_3c = local_3c + -1;
              } while (local_3c != 0);
            }
            if ((*(int *)(param_3[1] + 0x1f8) != 0) && (local_3c = 0, 0 < iVar16)) {
              local_5c = local_54;
              do {
                if (local_6c < (float)*(double *)(param_3[1] + 0x208)) break;
                iVar15 = *(int *)(local_5c + *local_64);
                if (((iVar15 < param_10) && (iVar12 <= iVar15)) &&
                   (fVar18 = (float10)FUN_0069a090(), fVar18 == (float10)0.0)) {
                  fVar18 = (float10)FUN_0067d670();
                  *(float *)(iVar1 + iVar15 * 4) = (float)fVar18;
                  local_6c = local_6c - 1.0;
                }
                local_3c = local_3c + 1;
                local_5c = local_5c + 4;
              } while (local_3c < iVar16);
            }
            local_34 = local_34 + iVar16;
            local_54 = local_54 + iVar16 * 4;
            iVar15 = *param_3;
          } while (local_34 < iVar15);
        }
      }
      local_30 = local_30 + 1;
      piVar13 = piVar13 + 1;
      local_64 = local_64 + 1;
    } while (local_30 < *(int *)(param_4 + 0x484));
  }
  return;
}

