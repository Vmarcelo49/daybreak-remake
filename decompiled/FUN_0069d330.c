// Function: FUN_0069d330
// Address:  0x0069d330
// Source:   batch_decompile (mass dump)
// Hash:     04e3a2ebe5be203f


undefined4 FUN_0069d330(int *param_1,int *param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  piVar3 = param_1;
  iVar5 = param_1[9];
  if (param_1[8] <= iVar5) {
    return 0;
  }
  iVar6 = param_1[4] + iVar5 * 4;
  uVar2 = *(uint *)(param_1[4] + iVar5 * 4);
  if ((uVar2 & 0x400) != 0) {
    uVar2 = param_1[0x56];
    param_1[0x56] = uVar2 + 1;
    param_1[9] = iVar5 + 1;
    param_1[0x57] = param_1[0x57] + (uint)(0xfffffffe < uVar2);
    return 0xffffffff;
  }
  if ((param_2 == (int *)0x0) && (param_3 == 0)) {
    return 1;
  }
  uVar7 = uVar2 & 0xff;
  param_1 = (int *)(uVar2 & 0x200);
  uVar4 = uVar7;
  while (uVar4 == 0xff) {
    puVar1 = (uint *)(iVar6 + 4);
    iVar6 = iVar6 + 4;
    iVar5 = iVar5 + 1;
    uVar4 = *puVar1 & 0xff;
    if ((*puVar1 & 0x200) != 0) {
      param_1 = (int *)0x200;
    }
    uVar7 = uVar7 + uVar4;
  }
  if (param_2 != (int *)0x0) {
    param_2[3] = (int)param_1;
    param_2[2] = uVar2 & 0x100;
    *param_2 = piVar3[3] + *piVar3;
    param_2[6] = piVar3[0x56];
    param_2[7] = piVar3[0x57];
    iVar6 = piVar3[5];
    param_2[4] = *(int *)(iVar6 + iVar5 * 8);
    iVar6 = *(int *)(iVar6 + 4 + iVar5 * 8);
    param_2[1] = uVar7;
    param_2[5] = iVar6;
  }
  if (param_3 != 0) {
    uVar2 = piVar3[0x56];
    piVar3[3] = piVar3[3] + uVar7;
    piVar3[0x56] = uVar2 + 1;
    piVar3[9] = iVar5 + 1;
    piVar3[0x57] = piVar3[0x57] + (uint)(0xfffffffe < uVar2);
  }
  return 1;
}

