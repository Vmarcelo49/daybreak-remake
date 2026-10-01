// Function: FUN_00685580
// Address:  0x00685580
// Source:   batch_decompile (mass dump)
// Hash:     fc294a011a5b6979


undefined4 FUN_00685580(int param_1,int param_2,uint *param_3,undefined4 *param_4)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint *puVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  int *local_174;
  uint *local_170;
  int *local_16c;
  int local_168;
  int local_164;
  uint local_15c;
  int local_158;
  int local_154;
  int local_144 [16];
  uint local_104 [65];
  
  piVar16 = *(int **)(param_2 + 0x510);
  iVar10 = *(int *)(param_2 + 0x504);
  iVar15 = *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 4) + 0x1c);
  iVar11 = *(int *)(iVar15 + 0xb20);
  if (param_3 == (uint *)0x0) {
    FUN_0069d4c0(param_1 + 4,0,1);
    for (uVar8 = *(int *)(param_1 + 0x24) / 2 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
      *param_4 = 0;
      param_4 = param_4 + 1;
    }
    for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1) {
      *(undefined1 *)param_4 = 0;
      param_4 = (undefined4 *)((int)param_4 + 1);
    }
    DAT_006d8948 = DAT_006d8948 + 1;
    return 0;
  }
  puVar13 = param_3;
  local_174 = (int *)iVar10;
  if (0 < iVar10) {
    do {
      uVar8 = *puVar13 & 0x7fff;
      switch(piVar16[0xd0]) {
      case 1:
        uVar8 = (int)uVar8 >> 2;
        break;
      case 2:
        uVar8 = (int)uVar8 >> 3;
        break;
      case 3:
        uVar8 = uVar8 / 0xc;
        break;
      case 4:
        uVar8 = (int)uVar8 >> 4;
      }
      *puVar13 = *puVar13 & 0x8000 | uVar8;
      local_174 = (int *)((int)local_174 + -1);
      puVar13 = puVar13 + 1;
    } while (local_174 != (int *)0x0);
  }
  local_104[0] = *param_3;
  local_104[1] = param_3[1];
  if (2 < iVar10) {
    local_16c = piVar16 + 0xd3;
    puVar13 = param_3 + 2;
    piVar2 = (int *)(param_2 + 0x30c);
    local_15c = iVar10 + -2;
    do {
      iVar10 = piVar2[0x3f];
      iVar4 = *piVar2;
      uVar3 = FUN_00684df0(piVar16[iVar10 + 0xd1],piVar16[iVar4 + 0xd1],param_3[iVar10],
                           param_3[iVar4],*local_16c);
      uVar8 = *puVar13;
      if (((uVar8 & 0x8000) == 0) && (uVar3 != uVar8)) {
        uVar12 = *(int *)(param_2 + 0x50c) - uVar3;
        if ((int)uVar3 <= (int)uVar12) {
          uVar12 = uVar3;
        }
        iVar9 = uVar8 - uVar3;
        if (iVar9 < 0) {
          if (iVar9 < (int)-uVar12) {
            iVar9 = (uVar12 - iVar9) + -1;
          }
          else {
            iVar9 = iVar9 * -2 + -1;
          }
        }
        else if (iVar9 < (int)uVar12) {
          iVar9 = iVar9 * 2;
        }
        else {
          iVar9 = iVar9 + uVar12;
        }
        *(int *)(((int)local_104 - (int)param_3) + (int)puVar13) = iVar9;
        param_3[iVar10] = param_3[iVar10] & 0x7fff;
        param_3[iVar4] = param_3[iVar4] & 0x7fff;
      }
      else {
        *puVar13 = uVar3 | 0x8000;
        *(undefined4 *)(((int)local_104 - (int)param_3) + (int)puVar13) = 0;
      }
      piVar2 = piVar2 + 1;
      local_16c = local_16c + 1;
      puVar13 = puVar13 + 1;
      local_15c = local_15c + -1;
    } while (local_15c != 0);
  }
  iVar10 = param_1 + 4;
  FUN_0069d4c0(iVar10,1,1);
  *(int *)(param_2 + 0x51c) = *(int *)(param_2 + 0x51c) + 1;
  iVar4 = FUN_00682f70(*(int *)(param_2 + 0x50c) + -1);
  *(int *)(param_2 + 0x518) = *(int *)(param_2 + 0x518) + iVar4 * 2;
  uVar5 = FUN_00682f70(*(int *)(param_2 + 0x50c) + -1);
  FUN_0069d4c0(iVar10,local_104[0],uVar5);
  uVar5 = FUN_00682f70(*(int *)(param_2 + 0x50c) + -1);
  FUN_0069d4c0(iVar10,local_104[1],uVar5);
  local_158 = 0;
  local_164 = 2;
  local_174 = piVar16;
  if (0 < *piVar16) {
    do {
      local_174 = local_174 + 1;
      local_144[0] = 0;
      local_144[1] = 0;
      iVar4 = *local_174;
      local_144[2] = 0;
      local_144[3] = 0;
      iVar9 = piVar16[iVar4 + 0x30];
      iVar1 = piVar16[iVar4 + 0x20];
      iVar14 = 1 << ((byte)iVar9 & 0x1f);
      local_144[4] = 0;
      local_144[5] = 0;
      local_144[6] = 0;
      local_144[7] = 0;
      local_15c = 0;
      local_154 = 0;
      if (iVar9 != 0) {
        if (0 < iVar14) {
          piVar2 = local_144 + 8;
          piVar6 = piVar16 + (iVar4 + 10) * 8;
          local_170 = (uint *)iVar14;
          do {
            if (*piVar6 < 0) {
              *piVar2 = 1;
            }
            else {
              *piVar2 = *(int *)(*(int *)(iVar15 + 0x720 + *piVar6 * 4) + 4);
            }
            piVar6 = piVar6 + 1;
            piVar2 = piVar2 + 1;
            local_170 = (uint *)((int)local_170 + -1);
          } while (local_170 != (uint *)0x0);
        }
        if (0 < iVar1) {
          piVar2 = local_144;
          local_170 = local_104 + local_164;
          local_168 = iVar1;
          do {
            iVar7 = 0;
            if (0 < iVar14) {
              piVar6 = local_144 + 8;
              do {
                if ((int)*local_170 < *piVar6) {
                  *piVar2 = iVar7;
                  break;
                }
                iVar7 = iVar7 + 1;
                piVar6 = piVar6 + 1;
              } while (iVar7 < iVar14);
            }
            iVar7 = *piVar2;
            local_170 = local_170 + 1;
            piVar2 = piVar2 + 1;
            local_15c = local_15c | iVar7 << ((byte)local_154 & 0x1f);
            local_154 = local_154 + iVar9;
            local_168 = local_168 + -1;
          } while (local_168 != 0);
        }
        iVar9 = FUN_0067e830(iVar11 + piVar16[iVar4 + 0x40] * 0x2c,local_15c,iVar10);
        *(int *)(param_2 + 0x514) = *(int *)(param_2 + 0x514) + iVar9;
      }
      if (0 < iVar1) {
        piVar2 = local_144;
        puVar13 = local_104 + local_164;
        local_168 = iVar1;
        do {
          if (-1 < piVar16[iVar4 * 8 + 0x50 + *piVar2]) {
            iVar9 = iVar11 + piVar16[iVar4 * 8 + 0x50 + *piVar2] * 0x2c;
            if ((int)*puVar13 < *(int *)(iVar9 + 4)) {
              iVar9 = FUN_0067e830(iVar9,*puVar13,iVar10);
              *(int *)(param_2 + 0x518) = *(int *)(param_2 + 0x518) + iVar9;
            }
          }
          piVar2 = piVar2 + 1;
          puVar13 = puVar13 + 1;
          local_168 = local_168 + -1;
        } while (local_168 != 0);
      }
      local_164 = local_164 + iVar1;
      local_158 = local_158 + 1;
    } while (local_158 < *piVar16);
  }
  iVar15 = 0;
  iVar10 = piVar16[0xd0] * *param_3;
  local_164 = 1;
  if (1 < *(int *)(param_2 + 0x504)) {
    local_174 = (int *)(param_2 + 0x108);
    iVar11 = iVar10;
    iVar4 = 0;
    do {
      uVar8 = param_3[*local_174] & 0x7fff;
      iVar10 = iVar11;
      iVar9 = iVar4;
      if (uVar8 == param_3[*local_174]) {
        iVar9 = piVar16[*local_174 + 0xd1];
        iVar10 = piVar16[0xd0] * uVar8;
        FUN_00685b70(iVar4,iVar9,iVar11,iVar10,param_4);
        iVar15 = iVar9;
      }
      local_174 = local_174 + 1;
      local_164 = local_164 + 1;
      iVar11 = iVar10;
      iVar4 = iVar9;
    } while (local_164 < *(int *)(param_2 + 0x504));
  }
  if (iVar15 < *(int *)(param_1 + 0x24) / 2) {
    piVar16 = param_4 + iVar15;
    do {
      *piVar16 = iVar10;
      iVar15 = iVar15 + 1;
      piVar16 = piVar16 + 1;
    } while (iVar15 < *(int *)(param_1 + 0x24) / 2);
  }
  DAT_006d8948 = DAT_006d8948 + 1;
  return 1;
}

