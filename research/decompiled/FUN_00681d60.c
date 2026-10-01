// Function: FUN_00681d60
// Address:  0x00681d60
// Source:   batch_decompile (mass dump)
// Hash:     1c2d3ef5281356af


void FUN_00681d60(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar2 = param_1;
    for (iVar1 = 0x322; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    _free(param_1);
  }
  return;
}

