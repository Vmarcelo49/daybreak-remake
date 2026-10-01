// Function: FUN_0067cef0
// Address:  0x0067cef0
// Source:   batch_decompile (mass dump)
// Hash:     91647cebd6b82d62


int * FUN_0067cef0(undefined4 param_1,int param_2,int *param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  undefined4 *puVar9;
  float10 fVar10;
  int local_10;
  
  iVar1 = *param_3;
  piVar5 = (int *)FUN_0067a2c0(param_1,*(int *)(param_4 + 0x484) << 2);
  local_10 = 0;
  iVar2 = *(int *)(param_2 + 0xa0 + *(int *)param_3[1] * 0x3c);
  if (0 < *(int *)(param_4 + 0x484)) {
    piVar8 = (int *)(param_4 + 0x888);
    piVar7 = piVar5;
    do {
      puVar3 = *(undefined4 **)(param_5 + piVar8[-0x100] * 4);
      iVar4 = *(int *)(param_5 + *piVar8 * 4);
      iVar6 = FUN_0067a2c0(param_1,iVar1 * 4);
      *piVar7 = iVar6;
      iVar6 = 0;
      if (0 < iVar2) {
        puVar9 = puVar3;
        do {
          fVar10 = (float10)FUN_0067d040(*puVar9,*(undefined4 *)
                                                  ((iVar4 - (int)puVar3) + (int)puVar9));
          puVar9 = puVar9 + 1;
          *(float *)(*piVar7 + iVar6 * 4) = (float)fVar10;
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar2);
      }
      if (iVar6 < iVar1) {
        puVar9 = puVar3 + iVar6;
        do {
          fVar10 = (float10)FUN_0067d110(*puVar9,*(undefined4 *)
                                                  ((int)puVar9 + (iVar4 - (int)puVar3)));
          puVar9 = puVar9 + 1;
          *(float *)(*piVar7 + iVar6 * 4) = (float)fVar10;
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar1);
      }
      local_10 = local_10 + 1;
      piVar8 = piVar8 + 1;
      piVar7 = piVar7 + 1;
    } while (local_10 < *(int *)(param_4 + 0x484));
  }
  return piVar5;
}

