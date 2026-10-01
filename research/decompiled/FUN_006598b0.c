// Function: FUN_006598b0
// Address:  0x006598b0
// Source:   batch_decompile (mass dump)
// Hash:     6b77c35e3cd985d4


undefined4 * FUN_006598b0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  while (param_1 != param_2) {
    param_2 = param_2 + -0x14;
    param_3 = param_3 + -0x14;
    puVar2 = param_2;
    puVar3 = param_3;
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return param_3;
}

