// ============================================
// Address:  0x0067ce60
// Original: FUN_0067ce60
// Status:   unreviewed
// ============================================


void FUN_0067ce60(int *param_1,int param_2,float *param_3,int param_4,int param_5)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  
  iVar3 = *param_1;
  fVar1 = *(float *)(param_1[1] + 0xc + param_4 * 4);
  iVar5 = 0;
  if (0 < iVar3) {
    param_2 = param_2 - (int)param_3;
    param_5 = param_5 - (int)param_3;
    do {
      fVar2 = *(float *)(*(int *)(param_1[3] + param_4 * 4) + iVar5 * 4) +
              *(float *)(param_2 + (int)param_3);
      if (*(float *)(param_1[1] + 0x6c) < fVar2) {
        fVar2 = *(float *)(param_1[1] + 0x6c);
      }
      fVar4 = fVar1 + *param_3;
      if (fVar2 <= fVar4) {
        fVar2 = fVar4;
      }
      *(float *)((int)param_3 + param_5) = fVar2;
      iVar5 = iVar5 + 1;
      param_3 = param_3 + 1;
    } while (iVar5 < iVar3);
  }
  return;
}

