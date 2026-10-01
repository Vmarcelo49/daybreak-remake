// Function: FUN_00426ff0
// Address:  0x00426ff0
// Source:   batch_decompile (mass dump)
// Hash:     245867bc63ef4c36


void FUN_00426ff0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)FUN_00410cf0(0x80,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = *param_2;
      param_2 = param_2 + 1;
      puVar1 = puVar1 + 1;
    }
  }
  return;
}

