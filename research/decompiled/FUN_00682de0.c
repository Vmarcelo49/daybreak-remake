// Function: FUN_00682de0
// Address:  0x00682de0
// Source:   batch_decompile (mass dump)
// Hash:     6fc17ff708ad10e6


void FUN_00682de0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar2 = param_1;
    for (iVar1 = 0x1c5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    _free(param_1);
  }
  return;
}

