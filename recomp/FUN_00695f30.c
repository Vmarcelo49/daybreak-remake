// ============================================
// Address:  0x00695f30
// Original: FUN_00695f30
// Status:   unreviewed
// ============================================


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

