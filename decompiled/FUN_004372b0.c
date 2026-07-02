// Function: FUN_004372b0
// Address:  0x004372b0
// Source:   batch_decompile (mass dump)
// Hash:     d84eb785dc2d9471


undefined4 * FUN_004372b0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)FUN_0063c120(param_2);
  uVar1 = puVar2[1];
  *param_1 = *puVar2;
  param_1[1] = uVar1;
  return param_1;
}

