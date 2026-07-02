// ============================================
// Address:  0x00691440
// Original: FUN_00691440
// Status:   unreviewed
// ============================================


undefined4 FUN_00691440(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    FUN_0068d950(param_1 + -100);
    *param_2 = *(undefined4 *)(param_1 + 0x40);
    FUN_0068d9a0();
    uVar1 = 0;
  }
  return uVar1;
}

