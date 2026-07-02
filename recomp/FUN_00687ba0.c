// ============================================
// Address:  0x00687ba0
// Original: FUN_00687ba0
// Status:   unreviewed
// ============================================


undefined4 FUN_00687ba0(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_3 = *(undefined4 *)(param_1 + 8);
    uVar1 = 0;
  }
  return uVar1;
}

