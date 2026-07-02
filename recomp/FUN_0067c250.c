// ============================================
// Address:  0x0067c250
// Original: FUN_0067c250
// Status:   unreviewed
// ============================================


void FUN_0067c250(int *param_1,float *param_2,int param_3,int param_4,int param_5)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar2 = *param_1;
  if (iVar2 < param_5) {
    param_5 = iVar2;
  }
  iVar3 = 0;
  if (0 < param_5) {
    pfVar1 = param_2;
    iVar4 = param_5;
    do {
      iVar4 = iVar4 + -1;
      *(float *)((param_4 - (int)param_2) + -4 + (int)(pfVar1 + 1)) =
           *(float *)(&DAT_006be380 + *(int *)((param_3 - (int)param_2) + (int)pfVar1) * 4) *
           *pfVar1;
      pfVar1 = pfVar1 + 1;
      iVar3 = param_5;
    } while (iVar4 != 0);
  }
  if (iVar3 < iVar2) {
    puVar5 = (undefined4 *)(param_4 + iVar3 * 4);
    for (iVar2 = iVar2 - iVar3; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  return;
}

