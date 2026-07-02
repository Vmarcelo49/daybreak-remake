// ============================================
// Address:  0x0067f0b0
// Original: FUN_0067f0b0
// Status:   unreviewed
// ============================================


undefined4
FUN_0067f0b0(int *param_1,int param_2,int param_3,int param_4,undefined4 param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int local_8;
  
  local_8 = 0;
  param_6 = param_6 + param_3;
  param_3 = param_3 / param_4;
  iVar8 = 0;
  iVar1 = local_8;
  do {
    local_8 = iVar8;
    if (param_6 / param_4 <= param_3) {
      return 0;
    }
    iVar8 = param_1[10];
    iVar3 = FUN_0069d640(param_5,param_1[9]);
    if (iVar3 < 0) {
      iVar3 = param_1[2];
      uVar9 = 0;
LAB_0067f14c:
      iVar4 = FUN_0069d640(param_5,iVar8);
      while (iVar4 < 0) {
        if (iVar8 < 2) {
          if (iVar4 < 0) {
            return 0xffffffff;
          }
          break;
        }
        iVar8 = iVar8 + -1;
        iVar4 = FUN_0069d640(param_5,iVar8);
      }
      uVar5 = FUN_0067e570(iVar4);
      iVar4 = iVar3 - uVar9;
      if (1 < iVar4) {
        do {
          uVar7 = iVar4 >> 1;
          uVar2 = (uint)(uVar5 < *(uint *)(param_1[5] + (uVar7 + uVar9) * 4));
          iVar3 = iVar3 - (-uVar2 & uVar7);
          uVar9 = uVar9 + (uVar2 - 1 & uVar7);
          iVar4 = iVar3 - uVar9;
        } while (1 < iVar4);
      }
      if (iVar8 < *(char *)(param_1[7] + uVar9)) {
        FUN_0069d6f0(param_5,iVar8);
        return 0xffffffff;
      }
      FUN_0069d6f0(param_5,(int)*(char *)(param_1[7] + uVar9));
      local_8 = iVar1;
    }
    else {
      uVar5 = *(uint *)(param_1[8] + iVar3 * 4);
      if ((uVar5 & 0x80000000) != 0) {
        uVar9 = (int)uVar5 >> 0xf & 0x7fff;
        iVar3 = param_1[2] - (uVar5 & 0x7fff);
        goto LAB_0067f14c;
      }
      FUN_0069d6f0(param_5,(int)*(char *)(param_1[7] + -1 + uVar5));
      uVar9 = uVar5 - 1;
    }
    if (uVar9 == 0xffffffff) {
      return 0xffffffff;
    }
    pfVar6 = (float *)(param_1[4] + *param_1 * uVar9 * 4);
    iVar3 = 0;
    iVar8 = local_8;
    if (0 < *param_1) {
      do {
        iVar1 = *(int *)(param_2 + local_8 * 4);
        local_8 = local_8 + 1;
        *(float *)(iVar1 + param_3 * 4) = *(float *)(iVar1 + param_3 * 4) + *pfVar6;
        if (local_8 == param_4) {
          local_8 = 0;
          param_3 = param_3 + 1;
        }
        iVar3 = iVar3 + 1;
        pfVar6 = pfVar6 + 1;
        iVar8 = local_8;
        iVar1 = local_8;
      } while (iVar3 < *param_1);
    }
  } while( true );
}

