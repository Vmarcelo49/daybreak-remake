// ============================================
// Address:  0x00696280
// Original: FUN_00696280
// Status:   unreviewed
// ============================================


undefined4 FUN_00696280(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = 0xffffffff;
    uVar1 = 0;
  }
  return uVar1;
}

