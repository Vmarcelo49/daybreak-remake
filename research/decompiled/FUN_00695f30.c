// Function: FUN_00695f30
// Address:  0x00695f30
// Source:   batch_decompile (mass dump)
// Hash:     c4f7ba0077dadc92


undefined4 FUN_00695f30(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = 0;
    param_2[1] = 0;
    uVar1 = 0;
  }
  return uVar1;
}

