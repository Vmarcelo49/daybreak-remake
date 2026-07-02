// ============================================
// Address:  0x0067fbe0
// Original: FUN_0067fbe0
// Status:   unreviewed
// ============================================


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0067fbe0(uint param_1,float *param_2,int param_3,int param_4,float *param_5,float *param_6,
                 float *param_7,float *param_8,float *param_9,float *param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  float *pfVar18;
  int iVar19;
  float *pfVar20;
  float *pfVar21;
  float *pfVar22;
  float *pfVar23;
  int iVar24;
  float *pfVar25;
  float *pfVar26;
  float *pfVar27;
  int iVar28;
  uint uVar29;
  int iVar30;
  float10 fVar31;
  float10 fVar32;
  float *local_34;
  float *local_2c;
  float *local_28;
  int local_20;
  uint local_1c;
  int local_18;
  int local_c;
  
  iVar6 = param_1;
  iVar7 = (int)param_2 + 1 >> 1;
  iVar8 = (int)(param_1 + -1) >> 1;
  iVar9 = param_1 * param_3;
  fVar31 = (float10)fcos((float10)_DAT_006be830 / (float10)(int)param_2);
  iVar10 = param_1 * (int)param_2;
  fVar32 = (float10)fsin((float10)_DAT_006be830 / (float10)(int)param_2);
  if (param_1 != 1) {
    if (0 < param_4) {
      pfVar17 = param_9;
      iVar28 = param_4;
      do {
        *pfVar17 = *(float *)(((int)param_7 - (int)param_9) + (int)pfVar17);
        pfVar17 = pfVar17 + 1;
        iVar28 = iVar28 + -1;
      } while (iVar28 != 0);
    }
    if (1 < (int)param_2) {
      local_28 = (float *)((int)param_2 + -1);
      pfVar17 = param_8;
      do {
        pfVar17 = pfVar17 + iVar9;
        if (0 < param_3) {
          pfVar22 = pfVar17;
          iVar28 = param_3;
          do {
            *pfVar22 = *(float *)(((int)param_6 - (int)param_8) + (int)pfVar22);
            pfVar22 = pfVar22 + param_1;
            iVar28 = iVar28 + -1;
          } while (iVar28 != 0);
        }
        local_28 = (float *)((int)local_28 + -1);
      } while (local_28 != (float *)0x0);
    }
    if (param_3 < iVar8) {
      if (1 < (int)param_2) {
        iVar28 = 0;
        local_34 = (float *)((int)param_2 + -1);
        param_10 = (float *)((int)param_10 + -4 + param_1 * -4);
        do {
          iVar28 = iVar28 + iVar9 * 4;
          param_10 = param_10 + param_1;
          iVar11 = iVar28 + param_1 * -4;
          if (0 < param_3) {
            local_28 = (float *)param_3;
            pfVar17 = (float *)(iVar11 + (int)param_8);
            local_2c = (float *)(iVar11 + -4 + (int)param_6);
            do {
              pfVar17 = pfVar17 + param_1;
              local_2c = local_2c + param_1;
              if (2 < (int)param_1) {
                uVar29 = param_1 - 1 >> 1;
                pfVar22 = local_2c;
                pfVar23 = param_10;
                pfVar18 = pfVar17;
                do {
                  pfVar15 = pfVar22 + 2;
                  pfVar18 = pfVar18 + 2;
                  uVar29 = uVar29 - 1;
                  *(float *)(((int)param_8 - (int)param_6) + (int)pfVar15) =
                       pfVar22[2] * pfVar23[1] + pfVar22[3] * pfVar23[2];
                  *pfVar18 = pfVar23[1] * pfVar22[3] - *pfVar15 * pfVar23[2];
                  pfVar22 = pfVar15;
                  pfVar23 = pfVar23 + 2;
                } while (uVar29 != 0);
              }
              local_28 = (float *)((int)local_28 + -1);
            } while (local_28 != (float *)0x0);
          }
          local_34 = (float *)((int)local_34 + -1);
        } while (local_34 != (float *)0x0);
      }
    }
    else if (1 < (int)param_2) {
      pfVar22 = (float *)((int)param_10 + -4 + param_1 * -4);
      pfVar17 = param_6 + -1;
      local_28 = (float *)((int)param_2 + -1);
      pfVar23 = param_8;
      do {
        pfVar22 = pfVar22 + param_1;
        pfVar23 = pfVar23 + iVar9;
        pfVar17 = pfVar17 + iVar9;
        if (2 < (int)param_1) {
          param_10 = (float *)(param_1 - 1 >> 1);
          pfVar18 = pfVar17;
          pfVar15 = pfVar22;
          pfVar16 = pfVar23;
          do {
            pfVar26 = pfVar15 + 2;
            pfVar16 = pfVar16 + 2;
            pfVar18 = pfVar18 + 2;
            if (0 < param_3) {
              pfVar13 = pfVar18;
              iVar28 = param_3;
              pfVar20 = pfVar16;
              do {
                *(float *)((int)pfVar13 + ((int)param_8 - (int)param_6)) =
                     pfVar13[1] * *pfVar26 + *pfVar13 * pfVar15[1];
                pfVar25 = pfVar13 + 1;
                fVar3 = *pfVar13;
                pfVar13 = pfVar13 + param_1;
                *pfVar20 = *pfVar25 * pfVar15[1] - *pfVar26 * fVar3;
                pfVar20 = pfVar20 + param_1;
                iVar28 = iVar28 + -1;
              } while (iVar28 != 0);
            }
            param_10 = (float *)((int)param_10 - 1);
            pfVar15 = pfVar26;
          } while (param_10 != (float *)0x0);
        }
        local_28 = (float *)((int)local_28 + -1);
      } while (local_28 != (float *)0x0);
    }
    iVar11 = iVar9 * (int)param_2;
    iVar28 = 0;
    if (iVar8 < param_3) {
      if (1 < iVar7) {
        local_18 = iVar7 + -1;
        do {
          iVar28 = iVar28 + iVar9;
          iVar11 = iVar11 - iVar9;
          if (2 < (int)param_1) {
            local_1c = param_1 - 1 >> 1;
            iVar30 = iVar28 * 4;
            iVar24 = iVar28;
            do {
              iVar24 = iVar24 + 2;
              iVar30 = iVar30 + 8;
              iVar12 = iVar30 + param_1 * -4;
              if (0 < param_3) {
                iVar19 = (iVar24 - param_1) + (iVar11 - iVar28);
                pfVar17 = (float *)(iVar12 + (int)param_6);
                local_28 = param_6 + iVar19;
                pfVar22 = (float *)(iVar12 + -4 + (int)param_8);
                pfVar23 = param_8 + iVar19 + -1;
                local_20 = param_3;
                do {
                  pfVar18 = pfVar22 + param_1;
                  pfVar15 = pfVar23 + param_1;
                  pfVar22 = pfVar22 + param_1;
                  pfVar23 = pfVar23 + param_1;
                  pfVar17 = pfVar17 + param_1;
                  local_28 = local_28 + param_1;
                  *(float *)(((int)param_6 - (int)param_8) + (int)pfVar22) = *pfVar18 + *pfVar15;
                  *(float *)((int)pfVar23 + ((int)param_6 - (int)param_8)) = pfVar22[1] - pfVar23[1]
                  ;
                  *pfVar17 = pfVar23[1] + pfVar22[1];
                  *local_28 = *pfVar23 - *pfVar22;
                  local_20 = local_20 + -1;
                } while (local_20 != 0);
              }
              local_1c = local_1c - 1;
            } while (local_1c != 0);
          }
          local_18 = local_18 + -1;
        } while (local_18 != 0);
      }
    }
    else if (1 < iVar7) {
      pfVar22 = param_6 + iVar11;
      pfVar23 = param_8 + iVar11 + -1;
      pfVar17 = param_8 + -1;
      local_2c = (float *)(iVar7 + -1);
      pfVar18 = param_6;
      do {
        pfVar18 = pfVar18 + iVar9;
        pfVar17 = pfVar17 + iVar9;
        pfVar22 = pfVar22 + -iVar9;
        pfVar23 = pfVar23 + -iVar9;
        if (0 < param_3) {
          local_28 = (float *)param_3;
          pfVar15 = pfVar23;
          pfVar16 = pfVar18;
          pfVar26 = pfVar22;
          param_10 = pfVar17;
          do {
            if (2 < (int)param_1) {
              uVar29 = param_1 - 1 >> 1;
              pfVar13 = param_10;
              pfVar20 = pfVar15;
              pfVar25 = pfVar16;
              pfVar27 = pfVar26;
              do {
                pfVar21 = pfVar20 + 2;
                pfVar14 = pfVar13 + 2;
                pfVar25 = pfVar25 + 2;
                pfVar27 = pfVar27 + 2;
                uVar29 = uVar29 - 1;
                *(float *)(((int)param_6 - (int)param_8) + (int)pfVar14) = pfVar20[2] + pfVar13[2];
                *(float *)((int)pfVar21 + ((int)param_6 - (int)param_8)) = pfVar13[3] - pfVar20[3];
                *pfVar25 = pfVar20[3] + pfVar13[3];
                *pfVar27 = *pfVar21 - *pfVar14;
                pfVar13 = pfVar14;
                pfVar20 = pfVar21;
              } while (uVar29 != 0);
            }
            param_10 = param_10 + param_1;
            pfVar16 = pfVar16 + param_1;
            pfVar26 = pfVar26 + param_1;
            pfVar15 = pfVar15 + param_1;
            local_28 = (float *)((int)local_28 + -1);
          } while (local_28 != (float *)0x0);
        }
        local_2c = (float *)((int)local_2c + -1);
      } while (local_2c != (float *)0x0);
    }
  }
  if (0 < param_4) {
    pfVar17 = param_7;
    iVar28 = param_4;
    do {
      *pfVar17 = *(float *)(((int)param_9 - (int)param_7) + (int)pfVar17);
      pfVar17 = pfVar17 + 1;
      iVar28 = iVar28 + -1;
    } while (iVar28 != 0);
  }
  if (1 < iVar7) {
    iVar28 = 0;
    local_1c = iVar7 + -1;
    param_10 = (float *)((int)param_2 * param_4);
    do {
      iVar28 = iVar28 + iVar9 * 4;
      param_10 = (float *)((int)param_10 - iVar9);
      if (0 < param_3) {
        pfVar22 = (float *)(iVar28 + param_1 * -4 + (int)param_8);
        pfVar17 = param_8 + ((int)param_10 - param_1);
        local_18 = param_3;
        do {
          pfVar17 = pfVar17 + param_1;
          pfVar22 = pfVar22 + param_1;
          local_18 = local_18 + -1;
          *(float *)((int)pfVar22 + ((int)param_6 - (int)param_8)) = *pfVar17 + *pfVar22;
          *(float *)((int)pfVar17 + ((int)param_6 - (int)param_8)) = *pfVar17 - *pfVar22;
        } while (local_18 != 0);
      }
      local_1c = local_1c + -1;
    } while (local_1c != 0);
  }
  iVar28 = ((int)param_2 + -1) * param_4;
  if (1 < iVar7) {
    local_c = iVar7 + -1;
    fVar3 = 0.0;
    param_10 = param_9 + (int)param_2 * param_4;
    local_34 = param_9;
    fVar1 = 1.0;
    do {
      fVar5 = fVar1 * (float)fVar31 - fVar3 * (float)fVar32;
      local_34 = local_34 + param_4;
      param_10 = param_10 + -param_4;
      fVar3 = fVar3 * (float)fVar31 + fVar1 * (float)fVar32;
      if (0 < param_4) {
        pfVar15 = param_7 + param_4;
        pfVar17 = local_34;
        pfVar22 = param_7;
        iVar11 = param_4;
        pfVar23 = param_7 + iVar28;
        pfVar18 = param_10;
        do {
          fVar1 = *pfVar15;
          pfVar15 = pfVar15 + 1;
          fVar2 = *pfVar22;
          pfVar22 = pfVar22 + 1;
          iVar11 = iVar11 + -1;
          *pfVar17 = fVar5 * fVar1 + fVar2;
          *pfVar18 = fVar3 * *pfVar23;
          pfVar17 = pfVar17 + 1;
          pfVar23 = pfVar23 + 1;
          pfVar18 = pfVar18 + 1;
        } while (iVar11 != 0);
      }
      if (2 < iVar7) {
        local_20 = iVar7 + -2;
        local_28 = param_7 + param_4;
        local_2c = param_7 + iVar28;
        fVar1 = fVar3;
        fVar2 = fVar5;
        do {
          fVar4 = fVar2 * fVar5 - fVar1 * fVar3;
          local_28 = local_28 + param_4;
          local_2c = local_2c + -param_4;
          fVar1 = fVar2 * fVar3 + fVar1 * fVar5;
          pfVar17 = local_34;
          pfVar22 = param_10;
          iVar11 = param_4;
          pfVar23 = local_28;
          pfVar18 = local_2c;
          if (0 < param_4) {
            do {
              iVar11 = iVar11 + -1;
              *pfVar17 = fVar4 * *pfVar23 + *pfVar17;
              *pfVar22 = fVar1 * *pfVar18 + *pfVar22;
              pfVar17 = pfVar17 + 1;
              pfVar22 = pfVar22 + 1;
              pfVar23 = pfVar23 + 1;
              pfVar18 = pfVar18 + 1;
            } while (iVar11 != 0);
          }
          local_20 = local_20 + -1;
          fVar2 = fVar4;
        } while (local_20 != 0);
      }
      local_c = local_c + -1;
      fVar1 = fVar5;
    } while (local_c != 0);
  }
  if (1 < iVar7) {
    param_6 = (float *)(iVar7 + -1);
    do {
      param_7 = param_7 + param_4;
      pfVar17 = param_9;
      pfVar22 = param_7;
      iVar28 = param_4;
      if (0 < param_4) {
        do {
          iVar28 = iVar28 + -1;
          *pfVar17 = *pfVar22 + *pfVar17;
          pfVar17 = pfVar17 + 1;
          pfVar22 = pfVar22 + 1;
        } while (iVar28 != 0);
      }
      param_6 = (float *)((int)param_6 + -1);
    } while (param_6 != (float *)0x0);
  }
  if ((int)param_1 < param_3) {
    if (0 < (int)param_1) {
      param_6 = (float *)param_1;
      pfVar17 = param_8;
      do {
        if (0 < param_3) {
          pfVar23 = (float *)(((int)param_5 - (int)param_8) + (int)pfVar17);
          pfVar22 = pfVar17;
          iVar28 = param_3;
          do {
            *pfVar23 = *pfVar22;
            pfVar22 = pfVar22 + param_1;
            pfVar23 = pfVar23 + iVar10;
            iVar28 = iVar28 + -1;
          } while (iVar28 != 0);
        }
        pfVar17 = pfVar17 + 1;
        param_6 = (float *)((int)param_6 + -1);
      } while (param_6 != (float *)0x0);
    }
  }
  else if (0 < param_3) {
    param_4 = param_3;
    param_6 = param_8;
    pfVar17 = param_5;
    do {
      pfVar22 = param_6;
      pfVar23 = pfVar17;
      iVar28 = param_1;
      if (0 < (int)param_1) {
        do {
          *pfVar23 = *pfVar22;
          iVar28 = iVar28 + -1;
          pfVar22 = pfVar22 + 1;
          pfVar23 = pfVar23 + 1;
        } while (iVar28 != 0);
      }
      param_6 = param_6 + param_1;
      pfVar17 = pfVar17 + iVar10;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  iVar28 = iVar9 * (int)param_2;
  if (1 < iVar7) {
    pfVar17 = param_8 + iVar28;
    param_2 = (float *)(iVar7 + -1);
    pfVar22 = param_5;
    pfVar23 = param_8;
    do {
      pfVar22 = pfVar22 + param_1 * 2;
      pfVar23 = pfVar23 + iVar9;
      pfVar17 = pfVar17 + -iVar9;
      if (0 < param_3) {
        param_6 = (float *)param_3;
        pfVar18 = pfVar22;
        pfVar15 = pfVar23;
        pfVar16 = pfVar17;
        do {
          fVar3 = *pfVar15;
          pfVar15 = pfVar15 + param_1;
          pfVar18[-1] = fVar3;
          *pfVar18 = *pfVar16;
          pfVar18 = pfVar18 + iVar10;
          pfVar16 = pfVar16 + param_1;
          param_6 = (float *)((int)param_6 + -1);
        } while (param_6 != (float *)0x0);
      }
      param_2 = (float *)((int)param_2 + -1);
    } while (param_2 != (float *)0x0);
  }
  if (param_1 != 1) {
    if (iVar8 < param_3) {
      iVar8 = -param_1;
      local_34 = (float *)0x0;
      if (1 < iVar7) {
        iVar11 = 0;
        param_6 = (float *)(iVar28 * 4);
        iVar28 = -2;
        local_c = iVar7 + -1;
        pfVar17 = param_5 + -2;
        do {
          iVar7 = iVar6 * 2;
          iVar11 = iVar11 + iVar9 * 4;
          iVar8 = iVar8 + iVar7;
          iVar28 = iVar28 + iVar7;
          pfVar17 = pfVar17 + iVar6 * 2;
          local_34 = (float *)((int)local_34 + iVar7);
          param_6 = (float *)((int)param_6 + iVar9 * -4);
          if (2 < iVar6) {
            param_7 = (float *)0x4;
            param_1 = iVar6 - 1U >> 1;
            pfVar22 = pfVar17;
            param_2 = (float *)iVar28;
            iVar7 = iVar11;
            do {
              iVar7 = iVar7 + 8;
              if (0 < param_3) {
                pfVar23 = (float *)(iVar7 + (int)param_8);
                pfVar16 = (float *)((iVar7 - iVar11) + (int)param_6 + (int)param_8);
                pfVar18 = param_5 + (((int)param_2 - iVar8) - iVar6) + (int)param_7 + (int)local_34;
                param_4 = param_3;
                pfVar15 = pfVar22;
                do {
                  pfVar18[-1] = pfVar23[-1] + pfVar16[-1];
                  pfVar15[-1] = pfVar23[-1] - pfVar16[-1];
                  *pfVar18 = *pfVar16 + *pfVar23;
                  fVar3 = *pfVar16;
                  fVar1 = *pfVar23;
                  pfVar16 = pfVar16 + iVar6;
                  pfVar23 = pfVar23 + iVar6;
                  pfVar18 = pfVar18 + iVar10;
                  *pfVar15 = fVar3 - fVar1;
                  pfVar15 = pfVar15 + iVar10;
                  param_4 = param_4 + -1;
                } while (param_4 != 0);
              }
              pfVar22 = pfVar22 + -2;
              param_2 = (float *)((int)param_2 + -2);
              param_7 = (float *)((int)param_7 + 4);
              param_1 = param_1 - 1;
            } while (param_1 != 0);
          }
          local_c = local_c + -1;
        } while (local_c != 0);
        return;
      }
    }
    else if (1 < iVar7) {
      pfVar22 = param_8 + 2;
      pfVar17 = param_5 + 2;
      param_5 = param_5 + -2;
      param_9 = (float *)(iVar7 + -1);
      param_8 = param_8 + iVar28 + 2;
      do {
        pfVar22 = pfVar22 + iVar9;
        param_5 = param_5 + param_1 * 2;
        pfVar17 = pfVar17 + param_1 * 2;
        param_8 = param_8 + -iVar9;
        if (0 < param_3) {
          param_4 = param_3;
          pfVar23 = pfVar17;
          param_2 = pfVar22;
          param_6 = param_5;
          param_7 = param_8;
          do {
            if (2 < (int)param_1) {
              uVar29 = param_1 - 1 >> 1;
              pfVar18 = param_7;
              pfVar15 = param_2;
              pfVar16 = pfVar23;
              pfVar26 = param_6;
              do {
                uVar29 = uVar29 - 1;
                pfVar16[-1] = pfVar15[-1] + pfVar18[-1];
                pfVar26[-1] = pfVar15[-1] - pfVar18[-1];
                *pfVar16 = *pfVar15 + *pfVar18;
                *pfVar26 = *pfVar18 - *pfVar15;
                pfVar18 = pfVar18 + 2;
                pfVar15 = pfVar15 + 2;
                pfVar16 = pfVar16 + 2;
                pfVar26 = pfVar26 + -2;
              } while (uVar29 != 0);
            }
            pfVar23 = pfVar23 + iVar10;
            param_6 = param_6 + iVar10;
            param_2 = param_2 + param_1;
            param_7 = param_7 + param_1;
            param_4 = param_4 + -1;
          } while (param_4 != 0);
        }
        param_9 = (float *)((int)param_9 + -1);
      } while (param_9 != (float *)0x0);
    }
  }
  return;
}

