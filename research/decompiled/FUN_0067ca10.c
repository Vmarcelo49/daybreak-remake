// Function: FUN_0067ca10
// Address:  0x0067ca10
// Source:   batch_decompile (mass dump)
// Hash:     cdc2715ea0af055e


void FUN_0067ca10(int *param_1,int param_2,int param_3,int param_4,undefined4 param_5,float param_6)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  
  iVar8 = 0;
  iVar4 = *param_1;
  fVar2 = *(float *)(param_1[1] + 0x1f0);
  if (0 < iVar4) {
    do {
      iVar7 = iVar8 + 1;
      fVar3 = *(float *)(param_3 + iVar8 * 4);
      iVar6 = *(int *)(param_1[5] + iVar8 * 4);
      pfVar5 = (float *)(param_3 + iVar8 * 4);
      if (iVar7 < iVar4) {
        piVar9 = (int *)(param_1[5] + iVar7 * 4);
        do {
          if (*piVar9 != iVar6) break;
          pfVar1 = pfVar5 + 1;
          pfVar5 = pfVar5 + 1;
          iVar8 = iVar8 + 1;
          piVar9 = piVar9 + 1;
          iVar7 = iVar7 + 1;
          if (fVar3 < *pfVar1) {
            fVar3 = *pfVar5;
          }
        } while (iVar7 < iVar4);
      }
      if (*(float *)(param_4 + iVar8 * 4) < fVar3 + 6.0) {
        iVar6 = iVar6 >> ((byte)param_1[8] & 0x1f);
        if (iVar6 < 0x11) {
          if (iVar6 < 0) {
            iVar6 = 0;
          }
        }
        else {
          iVar6 = 0x10;
        }
        FUN_0067caf0(param_5,*(undefined4 *)(param_2 + iVar6 * 4),fVar3,
                     *(int *)(param_1[5] + iVar8 * 4) - param_1[7],param_1[10],param_1[9],
                     fVar2 - param_6);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar4);
  }
  return;
}

