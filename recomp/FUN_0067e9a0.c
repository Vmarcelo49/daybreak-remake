// ============================================
// Address:  0x0067e9a0
// Original: FUN_0067e9a0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

undefined4 FUN_0067e9a0(int *param_1,float *param_2,float *param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int aiStack_34 [3];
  int *local_10;
  int local_c;
  
  param_4 = param_4 / *param_1;
  aiStack_34[2] = 0x67e9ca;
  local_10 = (int *)(&stack0xffffffd8 + param_4 * -8);
  aiStack_34[2 - param_4] = 0x67e9d9;
  local_c = 0;
  if (0 < param_4) {
    do {
      iVar8 = param_1[10];
      aiStack_34[param_4 * -2 + 2] = param_1[9];
      aiStack_34[param_4 * -2 + 1] = (int)param_3;
      aiStack_34[param_4 * -2] = 0x67ea0b;
      iVar2 = FUN_0069d640();
      if (iVar2 < 0) {
        iVar2 = param_1[2];
        uVar9 = 0;
LAB_0067ea58:
        aiStack_34[param_4 * -2 + 2] = iVar8;
        aiStack_34[param_4 * -2 + 1] = (int)param_3;
        aiStack_34[param_4 * -2] = 0x67ea65;
        iVar3 = FUN_0069d640();
        while (iVar3 < 0) {
          if (iVar8 < 2) {
            if (iVar3 < 0) goto LAB_0067eafe;
            break;
          }
          iVar8 = iVar8 + -1;
          aiStack_34[param_4 * -2 + 2] = iVar8;
          aiStack_34[param_4 * -2 + 1] = (int)param_3;
          aiStack_34[param_4 * -2] = 0x67ea7c;
          iVar3 = FUN_0069d640();
        }
        aiStack_34[param_4 * -2 + 2] = iVar3;
        aiStack_34[param_4 * -2 + 1] = 0x67ea95;
        uVar4 = FUN_0067e570();
        iVar3 = iVar2 - uVar9;
        if (1 < iVar3) {
          do {
            uVar7 = iVar3 >> 1;
            uVar1 = (uint)(uVar4 < *(uint *)(param_1[5] + (uVar7 + uVar9) * 4));
            iVar2 = iVar2 - (-uVar1 & uVar7);
            uVar9 = uVar9 + (uVar1 - 1 & uVar7);
            iVar3 = iVar2 - uVar9;
          } while (1 < iVar3);
        }
        if (iVar8 < *(char *)(param_1[7] + uVar9)) {
          aiStack_34[param_4 * -2 + 2] = iVar8;
          aiStack_34[param_4 * -2 + 1] = (int)param_3;
          aiStack_34[param_4 * -2] = 0x67eafb;
          FUN_0069d6f0();
LAB_0067eafe:
          uVar9 = 0xffffffff;
        }
        else {
          aiStack_34[param_4 * -2 + 2] = (int)*(char *)(param_1[7] + uVar9);
          aiStack_34[param_4 * -2 + 1] = (int)param_3;
          aiStack_34[param_4 * -2] = 0x67eaea;
          FUN_0069d6f0();
        }
      }
      else {
        uVar4 = *(uint *)(param_1[8] + iVar2 * 4);
        if ((uVar4 & 0x80000000) != 0) {
          uVar9 = (int)uVar4 >> 0xf & 0x7fff;
          iVar2 = param_1[2] - (uVar4 & 0x7fff);
          goto LAB_0067ea58;
        }
        aiStack_34[param_4 * -2 + 2] = (int)*(char *)(param_1[7] + -1 + uVar4);
        aiStack_34[param_4 * -2 + 1] = (int)param_3;
        aiStack_34[param_4 * -2] = 0x67ea4a;
        FUN_0069d6f0();
        uVar9 = uVar4 - 1;
      }
      local_10[param_4] = uVar9;
      if (uVar9 == 0xffffffff) {
        return 0xffffffff;
      }
      *local_10 = param_1[4] + *param_1 * uVar9 * 4;
      local_c = local_c + 1;
      local_10 = local_10 + 1;
    } while (local_c < param_4);
  }
  iVar8 = 0;
  if (0 < *param_1) {
    param_3 = param_2;
    do {
      pfVar5 = param_3;
      piVar6 = (int *)(&stack0xffffffd8 + param_4 * -8);
      iVar2 = param_4;
      if (0 < param_4) {
        do {
          iVar2 = iVar2 + -1;
          *pfVar5 = *(float *)(*piVar6 + iVar8 * 4) + *pfVar5;
          pfVar5 = pfVar5 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar2 != 0);
      }
      param_3 = param_3 + param_4;
      iVar8 = iVar8 + 1;
    } while (iVar8 < *param_1);
  }
  return 0;
}

