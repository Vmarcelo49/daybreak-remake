// Function: FUN_0067b150
// Address:  0x0067b150
// Source:   batch_decompile (mass dump)
// Hash:     ae4b25ed1f599741


undefined4 FUN_0067b150(int *param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  piVar1 = param_1 + 1;
  iVar2 = *(int *)(param_1[0x10] + 4);
  iVar5 = *(int *)(param_1[0x10] + 0x68);
  iVar3 = *(int *)(iVar2 + 0x1c);
  FUN_0067a330(param_1);
  FUN_0069d610(piVar1,*param_2,param_2[1]);
  iVar4 = FUN_0069d720(piVar1,1);
  if (iVar4 != 0) {
    return 0xffffff79;
  }
  iVar5 = FUN_0069d720(piVar1,*(undefined4 *)(iVar5 + 0x2c));
  if (iVar5 == -1) {
    return 0xffffff78;
  }
  param_1[10] = iVar5;
  iVar4 = **(int **)(iVar3 + 0x20 + iVar5 * 4);
  param_1[7] = iVar4;
  if (iVar4 == 0) {
    param_1[6] = 0;
    param_1[8] = 0;
  }
  else {
    iVar4 = FUN_0069d720(piVar1,1);
    param_1[6] = iVar4;
    iVar4 = FUN_0069d720(piVar1,1);
    param_1[8] = iVar4;
    if (iVar4 == -1) {
      return 0xffffff78;
    }
  }
  param_1[0xc] = param_2[4];
  param_1[0xd] = param_2[5];
  param_1[0xe] = param_2[6];
  param_1[0xf] = param_2[7];
  param_1[0xb] = param_2[3];
  param_1[9] = *(int *)(iVar3 + param_1[7] * 4);
  iVar4 = FUN_0067a2c0(param_1,*(int *)(iVar2 + 4) << 2);
  *param_1 = iVar4;
  iVar4 = 0;
  if (0 < *(int *)(iVar2 + 4)) {
    do {
      uVar6 = FUN_0067a2c0(param_1,param_1[9] << 2);
      *(undefined4 *)(*param_1 + iVar4 * 4) = uVar6;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(iVar2 + 4));
  }
  iVar2 = *(int *)(*(int *)(iVar3 + 0x20 + iVar5 * 4) + 0xc);
  uVar6 = (**(code **)((&PTR_PTR_006be814)[*(int *)(iVar3 + 0x120 + iVar2 * 4)] + 0x10))
                    (param_1,*(undefined4 *)(iVar3 + 0x220 + iVar2 * 4));
  return uVar6;
}

