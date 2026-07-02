// Function: FUN_0067b420
// Address:  0x0067b420
// Source:   batch_decompile (mass dump)
// Hash:     5d5204dd6d522e50


void FUN_0067b420(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar2 = param_1;
    for (iVar1 = 0x84; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    _free(param_1);
  }
  return;
}

