// Function: FUN_004380f0
// Address:  0x004380f0
// Source:   batch_decompile (mass dump)
// Hash:     597f6073b3fac06b


void FUN_004380f0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00410cf0(0x10,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_2;
    puVar1[1] = param_2[1];
    puVar1[2] = param_2[2];
    puVar1[3] = param_2[3];
  }
  return;
}

