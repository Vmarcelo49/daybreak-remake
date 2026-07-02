// Function: FUN_0067caf0
// Address:  0x0067caf0
// Source:   batch_decompile (mass dump)
// Hash:     f98c49a1f0ab1a1a


void FUN_0067caf0(int param_1,int param_2,float param_3,undefined4 param_4,int param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  
  uVar2 = __ftol();
  uVar2 = uVar2 & ((int)uVar2 < 1) - 1;
  if (6 < (int)uVar2) {
    uVar2 = 7;
  }
  iVar1 = *(int *)(param_2 + uVar2 * 4);
  iVar3 = __ftol();
  iVar4 = __ftol();
  iVar5 = __ftol();
  if (iVar5 < iVar3) {
    pfVar7 = (float *)(iVar1 + 8 + iVar5 * 4);
    pfVar6 = (float *)(param_1 + iVar4 * 4);
    do {
      if ((0 < iVar4) && (*pfVar6 < param_3 + *pfVar7)) {
        *pfVar6 = param_3 + *pfVar7;
      }
      iVar4 = iVar4 + param_6;
      pfVar6 = pfVar6 + param_6;
      if (param_5 <= iVar4) {
        return;
      }
      iVar5 = iVar5 + 1;
      pfVar7 = pfVar7 + 1;
    } while (iVar5 < iVar3);
  }
  return;
}

