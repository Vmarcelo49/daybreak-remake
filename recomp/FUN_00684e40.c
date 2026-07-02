// ============================================
// Address:  0x00684e40
// Original: FUN_00684e40
// Status:   unreviewed
// ============================================


int FUN_00684e40(int param_1,int param_2,int param_3,int param_4,float *param_5,int param_6,
                int param_7)

{
  float *pfVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  piVar2 = (int *)param_5;
  iVar5 = param_3;
  pfVar1 = (float *)(param_1 + param_3 * 4);
  FUN_00685030(pfVar1);
  piVar6 = (int *)param_5;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  iVar4 = 0;
  local_2c = 0;
  local_24 = 0;
  local_1c = 0;
  local_14 = 0;
  local_c = 0;
  local_28 = 0;
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  local_8 = 0;
  param_3 = 0;
  *param_5 = (float)iVar5;
  param_5[1] = (float)param_4;
  if (param_6 <= param_4) {
    param_4 = param_6 + -1;
  }
  if (iVar5 <= param_4) {
    param_5 = pfVar1;
    do {
      iVar3 = FUN_00685030(param_5);
      if (iVar3 != 0) {
        if (*(float *)((param_2 - param_1) + (int)param_5) + *(float *)(param_7 + 0x458) < *param_5)
        {
          local_20 = local_20 + iVar3;
          local_28 = local_28 + iVar5;
          local_18 = local_18 + iVar5 * iVar5;
          local_10 = local_10 + iVar3 * iVar3;
          local_8 = local_8 + iVar3 * iVar5;
          param_3 = param_3 + 1;
        }
        else {
          local_24 = local_24 + iVar3;
          local_2c = local_2c + iVar5;
          local_1c = local_1c + iVar5 * iVar5;
          local_14 = local_14 + iVar3 * iVar3;
          local_c = local_c + iVar3 * iVar5;
          iVar4 = iVar4 + 1;
        }
      }
      iVar5 = iVar5 + 1;
      param_5 = param_5 + 1;
    } while (iVar5 <= param_4);
  }
  iVar3 = __ftol();
  iVar5 = iVar3 + 1;
  piVar2[2] = iVar5 * local_2c + local_28;
  piVar2[3] = iVar5 * local_24 + local_20;
  piVar2[4] = iVar5 * local_1c + local_18;
  piVar2[5] = iVar5 * local_14 + local_10;
  piVar2[6] = iVar5 * local_c + local_8;
  piVar2[7] = iVar3 * iVar4 + param_3 + iVar4;
  return iVar4;
}

