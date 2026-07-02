// ============================================
// Address:  0x0067cd00
// Original: FUN_0067cd00
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_0067cd00(float *param_1,int param_2,int param_3)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  int *piVar8;
  int iStack_2c;
  float fStack_28;
  int local_14;
  int local_10;
  int *local_c;
  float *local_8;
  
  fStack_28 = 9.53264e-39;
  iVar3 = param_3 * -4;
  pfVar7 = (float *)(&stack0xffffffdc + param_3 * -8);
  (&fStack_28)[-param_3] = 9.53266e-39;
  iVar5 = 0;
  iVar4 = 0;
  local_14 = 0;
  if (0 < param_3) {
    local_8 = param_1;
    do {
      if (1 < iVar4) {
        local_c = &iStack_2c + (iVar4 - param_3);
        for (pfVar6 = &fStack_28 + param_3 * -2 + iVar4; *pfVar6 <= *local_8; pfVar6 = pfVar6 + -1)
        {
          if (((((int)pfVar6[param_3] + param_2 <= iVar5) || (iVar4 < 2)) || (pfVar6[-1] < *pfVar6))
             || (*local_c + param_2 <= iVar5)) {
            *(int *)(&stack0xffffffdc + iVar4 * 4 + iVar3) = iVar5;
            fVar2 = *local_8;
            goto LAB_0067cdbe;
          }
          iVar4 = iVar4 + -1;
          local_c = local_c + -1;
        }
      }
      *(int *)(&stack0xffffffdc + iVar4 * 4 + iVar3) = iVar5;
      fVar2 = *local_8;
LAB_0067cdbe:
      *(float *)(&stack0xffffffdc + iVar4 * 4 + param_3 * -8) = fVar2;
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 1;
      local_8 = local_8 + 1;
    } while (iVar5 < param_3);
  }
  local_10 = 0;
  piVar1 = (int *)(&stack0xffffffdc + iVar3);
  if (0 < iVar4) {
    do {
      piVar8 = piVar1 + 1;
      if ((iVar4 + -1 <= local_10) || ((float)piVar8[-param_3] <= *pfVar7)) {
        iVar3 = *piVar1 + 1 + param_2;
      }
      else {
        iVar3 = *piVar8;
      }
      if (param_3 < iVar3) {
        iVar3 = param_3;
      }
      if (local_14 < iVar3) {
        iVar3 = iVar3 - local_14;
        pfVar6 = param_1 + local_14;
        local_14 = local_14 + iVar3;
        do {
          *pfVar6 = *pfVar7;
          pfVar6 = pfVar6 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      local_10 = local_10 + 1;
      pfVar7 = pfVar7 + 1;
      piVar1 = piVar8;
    } while (local_10 < iVar4);
  }
  return;
}

