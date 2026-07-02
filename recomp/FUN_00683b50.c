// ============================================
// Address:  0x00683b50
// Original: FUN_00683b50
// Status:   unreviewed
// ============================================


void FUN_00683b50(undefined4 param_1,int *param_2,int *param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  undefined4 *local_44;
  float local_38;
  int *local_34;
  int local_30;
  int local_2c;
  int local_28;
  
  piVar2 = (int *)*param_2;
  iVar3 = piVar2[3];
  iVar4 = piVar2[2];
  uVar5 = (piVar2[1] - *piVar2) / iVar4;
  puVar6 = (undefined4 *)FUN_0067a2c0(param_1,param_4 * 4);
  if (0 < param_4) {
    local_2c = param_4;
    local_44 = puVar6;
    do {
      puVar7 = (undefined4 *)FUN_0067a2c0(param_1,uVar5 * 4);
      *local_44 = puVar7;
      for (uVar8 = uVar5 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
        *(undefined1 *)puVar7 = 0;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
      }
      local_44 = local_44 + 1;
      local_2c = local_2c + -1;
    } while (local_2c != 0);
  }
  local_30 = 0;
  if (0 < (int)uVar5) {
    local_2c = 0;
    do {
      iVar9 = *piVar2;
      if (0 < param_4) {
        local_34 = param_3;
        local_28 = param_4;
        do {
          local_38 = 0.0;
          if (0 < iVar4) {
            iVar11 = (iVar9 + local_2c) * 4;
            iVar12 = iVar4;
            do {
              pfVar10 = (float *)(*local_34 + iVar11);
              if (local_38 < ABS(*pfVar10)) {
                local_38 = ABS(*pfVar10);
              }
              FUN_0069a090((double)(*pfVar10 + 0.5));
              iVar11 = iVar11 + 4;
              iVar12 = iVar12 + -1;
            } while (iVar12 != 0);
          }
          iVar11 = 0;
          if (0 < iVar3 + -1) {
            pfVar10 = (float *)(piVar2 + 0x185);
            do {
              if ((local_38 <= pfVar10[-0x40]) &&
                 ((*pfVar10 < 0.0 || (iVar12 = __ftol(), (float)iVar12 < *pfVar10)))) break;
              iVar11 = iVar11 + 1;
              pfVar10 = pfVar10 + 1;
            } while (iVar11 < iVar3 + -1);
          }
          piVar1 = (int *)(((int)puVar6 - (int)param_3) + (int)local_34);
          local_34 = local_34 + 1;
          local_28 = local_28 + -1;
          *(int *)(*piVar1 + local_30 * 4) = iVar11;
        } while (local_28 != 0);
      }
      local_2c = local_2c + iVar4;
      local_30 = local_30 + 1;
    } while (local_30 < (int)uVar5);
  }
  param_2[10] = param_2[10] + 1;
  return;
}

