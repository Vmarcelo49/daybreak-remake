// ============================================
// Address:  0x0067ef30
// Original: FUN_0067ef30
// Status:   unreviewed
// ============================================


undefined4 FUN_0067ef30(int *param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int local_4;
  
  iVar9 = 0;
  local_4 = 0;
  if (0 < param_4) {
    do {
      iVar7 = param_1[10];
      iVar2 = FUN_0069d640(param_3,param_1[9]);
      if (iVar2 < 0) {
        iVar9 = param_1[2];
        uVar8 = 0;
LAB_0067efac:
        iVar2 = FUN_0069d640(param_3,iVar7);
        while (iVar2 < 0) {
          if (iVar7 < 2) {
            if (iVar2 < 0) {
              return 0xffffffff;
            }
            break;
          }
          iVar7 = iVar7 + -1;
          iVar2 = FUN_0069d640(param_3,iVar7);
        }
        uVar3 = FUN_0067e570(iVar2);
        iVar2 = iVar9 - uVar8;
        while (1 < iVar2) {
          uVar6 = iVar2 >> 1;
          uVar1 = (uint)(uVar3 < *(uint *)(param_1[5] + (uVar6 + uVar8) * 4));
          iVar9 = iVar9 - (-uVar1 & uVar6);
          uVar8 = uVar8 + (uVar1 - 1 & uVar6);
          iVar2 = iVar9 - uVar8;
        }
        if (iVar7 < *(char *)(param_1[7] + uVar8)) {
          FUN_0069d6f0(param_3,iVar7);
          return 0xffffffff;
        }
        FUN_0069d6f0(param_3,(int)*(char *)(param_1[7] + uVar8));
        iVar9 = local_4;
      }
      else {
        uVar3 = *(uint *)(param_1[8] + iVar2 * 4);
        if ((uVar3 & 0x80000000) != 0) {
          uVar8 = (int)uVar3 >> 0xf & 0x7fff;
          iVar9 = param_1[2] - (uVar3 & 0x7fff);
          goto LAB_0067efac;
        }
        FUN_0069d6f0(param_3,(int)*(char *)(param_1[7] + -1 + uVar3));
        uVar8 = uVar3 - 1;
      }
      if (uVar8 == 0xffffffff) {
        return 0xffffffff;
      }
      puVar5 = (undefined4 *)(param_1[4] + *param_1 * uVar8 * 4);
      iVar7 = 0;
      if (0 < *param_1) {
        puVar4 = (undefined4 *)(param_2 + iVar9 * 4);
        do {
          iVar9 = iVar9 + 1;
          *puVar4 = *puVar5;
          puVar4 = puVar4 + 1;
          iVar7 = iVar7 + 1;
          puVar5 = puVar5 + 1;
          local_4 = iVar9;
        } while (iVar7 < *param_1);
      }
    } while (iVar9 < param_4);
  }
  return 0;
}

