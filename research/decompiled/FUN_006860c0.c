// Function: FUN_006860c0
// Address:  0x006860c0
// Source:   batch_decompile (mass dump)
// Hash:     b9547d4e9a41ee3b


void FUN_006860c0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar2 = param_1;
    for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    _free(param_1);
  }
  return;
}

