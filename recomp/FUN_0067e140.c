// ============================================
// Address:  0x0067e140
// Original: FUN_0067e140
// Status:   unreviewed
// ============================================


undefined4 FUN_0067e140(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_1;
  for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[3] = param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[1];
  *param_1 = *param_2;
  uVar1 = FUN_0067dc10(param_2[2],param_2[1],0);
  param_1[5] = uVar1;
  uVar1 = FUN_0067de00(param_2,param_2[1],0);
  param_1[4] = uVar1;
  return 0;
}

