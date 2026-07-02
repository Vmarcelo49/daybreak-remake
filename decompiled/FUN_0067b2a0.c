// Function: FUN_0067b2a0
// Address:  0x0067b2a0
// Source:   batch_decompile (mass dump)
// Hash:     e5c7a9bc8fdc8111


undefined4 FUN_0067b2a0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  puVar1 = param_1 + 1;
  iVar4 = *(int *)(param_1[0x10] + 0x68);
  iVar2 = *(int *)(*(int *)(param_1[0x10] + 4) + 0x1c);
  FUN_0067a330(param_1);
  FUN_0069d610(puVar1,*param_2,param_2[1]);
  iVar3 = FUN_0069d720(puVar1,1);
  if (iVar3 != 0) {
    return 0xffffff79;
  }
  iVar4 = FUN_0069d720(puVar1,*(undefined4 *)(iVar4 + 0x2c));
  if (iVar4 == -1) {
    return 0xffffff78;
  }
  param_1[10] = iVar4;
  iVar4 = **(int **)(iVar2 + 0x20 + iVar4 * 4);
  param_1[7] = iVar4;
  if (iVar4 == 0) {
    param_1[6] = 0;
    param_1[8] = 0;
  }
  else {
    uVar5 = FUN_0069d720(puVar1,1);
    param_1[6] = uVar5;
    iVar4 = FUN_0069d720(puVar1,1);
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
  param_1[9] = 0;
  *param_1 = 0;
  return 0;
}

