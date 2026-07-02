// Function: FUN_00659a90
// Address:  0x00659a90
// Source:   batch_decompile (mass dump)
// Hash:     0a928f0dd7695db0


void FUN_00659a90(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)FUN_00410cf0(0x50,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = *param_2;
      param_2 = param_2 + 1;
      puVar1 = puVar1 + 1;
    }
  }
  return;
}

