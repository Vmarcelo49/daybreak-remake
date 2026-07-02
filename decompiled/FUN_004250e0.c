// Function: FUN_004250e0
// Address:  0x004250e0
// Source:   batch_decompile (mass dump)
// Hash:     718267b596221caf


undefined4 * FUN_004250e0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)FUN_00433040(param_2);
  uVar1 = puVar2[1];
  *param_1 = *puVar2;
  param_1[1] = uVar1;
  return param_1;
}

