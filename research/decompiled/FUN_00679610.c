// Function: FUN_00679610
// Address:  0x00679610
// Source:   batch_decompile (mass dump)
// Hash:     bb8c7cbba5bb9b35


float10 FUN_00679610(int param_1)

{
  uint uVar1;
  int iVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  longlong lVar10;
  uint local_18;
  int iStack_14;
  double local_10;
  
  iVar8 = 0;
  local_10 = 0.0;
  if (*(int *)(param_1 + 0x58) < 2) {
    return (float10)-131.0;
  }
  lVar4 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    lVar10 = FUN_006784b0(param_1,0xffffffff);
    fVar9 = (float10)FUN_00678520(param_1,0xffffffff);
    local_10 = (double)fVar9;
    iVar8 = *(int *)(param_1 + 0x34) + -1;
    lVar4 = lVar10;
    if (-1 < iVar8) {
      iVar7 = iVar8 * 0x10;
      do {
        iStack_14 = (int)((ulonglong)lVar10 >> 0x20);
        local_18 = (uint)lVar10;
        uVar1 = *(uint *)(*(int *)(param_1 + 0x44) + 8 + iVar7);
        iVar2 = *(int *)(*(int *)(param_1 + 0x44) + 0xc + iVar7);
        lVar3 = CONCAT44(iVar2,uVar1);
        iVar2 = (iStack_14 - iVar2) - (uint)(local_18 < uVar1);
        lVar6 = lVar10 - lVar3;
        lVar5 = lVar10 - lVar3;
        lVar4 = lVar10 - lVar3;
        lVar10 = lVar10 - lVar3;
        fVar9 = (float10)FUN_00678520(param_1,iVar8);
        local_10 = (double)((float10)local_10 - fVar9);
        if ((iVar2 < *(int *)(param_1 + 0x54)) ||
           ((iVar2 <= *(int *)(param_1 + 0x54) &&
            (lVar4 = lVar5, local_18 - uVar1 <= *(uint *)(param_1 + 0x50))))) break;
        iVar8 = iVar8 + -1;
        iVar7 = iVar7 + -0x10;
        lVar4 = lVar6;
      } while (-1 < iVar8);
    }
  }
  return (float10)CONCAT44((*(int *)(param_1 + 0x54) - (int)((ulonglong)lVar4 >> 0x20)) -
                           (uint)(*(uint *)(param_1 + 0x50) < (uint)lVar4),
                           *(uint *)(param_1 + 0x50) - (uint)lVar4) /
         (float10)*(int *)(*(int *)(param_1 + 0x48) + 8 + iVar8 * 0x20) + (float10)local_10;
}

