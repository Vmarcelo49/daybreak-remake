// ============================================
// Address:  0x00686b00
// Original: FUN_00686b00
// Status:   unreviewed
// ============================================


void __thiscall FUN_00686b00(int param_1,int param_2)

{
  if (param_2 == 0) {
    FUN_00686b30();
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 1;
    *(int *)(param_1 + 0x28) = param_2;
  }
  return;
}

