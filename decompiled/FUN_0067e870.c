// Function: FUN_0067e870
// Address:  0x0067e870
// Source:   batch_decompile (mass dump)
// Hash:     9d728fdb0800bd5e


uint FUN_0067e870(int param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  iVar6 = *(int *)(param_1 + 0x28);
  iVar2 = FUN_0069d640(param_2,*(undefined4 *)(param_1 + 0x24));
  if (iVar2 < 0) {
    iVar2 = *(int *)(param_1 + 8);
    uVar7 = 0;
  }
  else {
    uVar4 = *(uint *)(*(int *)(param_1 + 0x20) + iVar2 * 4);
    if ((uVar4 & 0x80000000) == 0) {
      FUN_0069d6f0(param_2,(int)*(char *)(*(int *)(param_1 + 0x1c) + -1 + uVar4));
      uVar7 = uVar4 - 1;
      goto LAB_0067e8d0;
    }
    uVar7 = (int)uVar4 >> 0xf & 0x7fff;
    iVar2 = *(int *)(param_1 + 8) - (uVar4 & 0x7fff);
  }
  iVar3 = FUN_0069d640(param_2,iVar6);
  while (iVar3 < 0) {
    if (iVar6 < 2) {
      if (iVar3 < 0) {
        return 0xffffffff;
      }
      break;
    }
    iVar6 = iVar6 + -1;
    iVar3 = FUN_0069d640(param_2,iVar6);
  }
  uVar4 = FUN_0067e570(iVar3);
  iVar3 = iVar2 - uVar7;
  if (1 < iVar3) {
    do {
      uVar5 = iVar3 >> 1;
      uVar1 = (uint)(uVar4 < *(uint *)(*(int *)(param_1 + 0x14) + (uVar5 + uVar7) * 4));
      iVar2 = iVar2 - (-uVar1 & uVar5);
      uVar7 = uVar7 + (uVar1 - 1 & uVar5);
      iVar3 = iVar2 - uVar7;
    } while (1 < iVar3);
  }
  iVar2 = (int)*(char *)(*(int *)(param_1 + 0x1c) + uVar7);
  if (iVar6 < iVar2) {
    FUN_0069d6f0(param_2,iVar6);
    return 0xffffffff;
  }
  FUN_0069d6f0(param_2,iVar2);
LAB_0067e8d0:
  if (-1 < (int)uVar7) {
    return *(uint *)(*(int *)(param_1 + 0x18) + uVar7 * 4);
  }
  return uVar7;
}

