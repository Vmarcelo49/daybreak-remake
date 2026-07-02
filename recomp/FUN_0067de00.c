// ============================================
// Address:  0x0067de00
// Original: FUN_0067de00
// Status:   unreviewed
// ============================================


void * FUN_0067de00(int *param_1,float param_2,int *param_3)

{
  float fVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float10 fVar10;
  int local_14;
  float local_8;
  
  piVar2 = param_1;
  iVar7 = 0;
  local_14 = 0;
  if ((param_1[3] != 1) && (param_1[3] != 2)) {
    return (void *)0x0;
  }
  fVar9 = (float10)FUN_0067dbc0(param_1[4]);
  fVar10 = (float10)FUN_0067dbc0(param_1[5]);
  pvVar3 = _calloc(*param_1 * (int)param_2,4);
  if (param_1[3] == 1) {
    iVar4 = FUN_0067dd90(param_1);
    if (0 < param_1[1]) {
      param_1 = param_3;
      do {
        if ((param_3 == (int *)0x0) || (*(int *)(piVar2[2] + iVar7 * 4) != 0)) {
          iVar5 = *piVar2;
          iVar8 = 0;
          local_8 = 0.0;
          iVar6 = 1;
          if (0 < iVar5) {
            do {
              fVar1 = ABS((float)*(int *)(piVar2[8] + ((iVar7 / iVar6) % iVar4) * 4)) *
                      (float)fVar10 + local_8 + (float)fVar9;
              if (piVar2[7] != 0) {
                local_8 = fVar1;
              }
              if (param_3 == (int *)0x0) {
                *(float *)((int)pvVar3 + (iVar5 * local_14 + iVar8) * 4) = fVar1;
              }
              else {
                *(float *)((int)pvVar3 + (iVar5 * *param_1 + iVar8) * 4) = fVar1;
              }
              iVar6 = iVar6 * iVar4;
              iVar5 = *piVar2;
              iVar8 = iVar8 + 1;
            } while (iVar8 < iVar5);
          }
          local_14 = local_14 + 1;
          param_1 = param_1 + 1;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < piVar2[1]);
    }
  }
  else if ((param_1[3] == 2) && (iVar7 = 0, 0 < param_1[1])) {
    param_1 = param_3;
    do {
      if ((param_3 == (int *)0x0) || (*(int *)(piVar2[2] + iVar7 * 4) != 0)) {
        iVar4 = *piVar2;
        iVar5 = 0;
        param_2 = 0.0;
        if (0 < iVar4) {
          do {
            fVar1 = ABS((float)*(int *)(piVar2[8] + (iVar4 * iVar7 + iVar5) * 4)) * (float)fVar10 +
                    param_2 + (float)fVar9;
            if (piVar2[7] != 0) {
              param_2 = fVar1;
            }
            if (param_3 == (int *)0x0) {
              *(float *)((int)pvVar3 + (iVar4 * local_14 + iVar5) * 4) = fVar1;
            }
            else {
              *(float *)((int)pvVar3 + (*param_1 * iVar4 + iVar5) * 4) = fVar1;
            }
            iVar4 = *piVar2;
            iVar5 = iVar5 + 1;
          } while (iVar5 < iVar4);
        }
        local_14 = local_14 + 1;
        param_1 = param_1 + 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < piVar2[1]);
    return pvVar3;
  }
  return pvVar3;
}

