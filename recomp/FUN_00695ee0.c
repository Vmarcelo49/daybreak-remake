// ============================================
// Address:  0x00695ee0
// Original: FUN_00695ee0
// Status:   unreviewed
// ============================================


undefined4 FUN_00695ee0(int param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined8 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    FUN_0068d950(*(undefined4 *)(param_1 + 0x34));
    *param_2 = *(undefined8 *)(param_1 + 0x28);
    FUN_0068d9a0();
    uVar1 = 0;
  }
  return uVar1;
}

