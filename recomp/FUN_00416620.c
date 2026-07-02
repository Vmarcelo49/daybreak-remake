// ============================================
// Address:  0x00416620
// Original: FUN_00416620
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00416620(int param_1,undefined1 *param_2)

{
  int local_8;
  
  *param_2 = 0xf;
  for (local_8 = 0; local_8 < 9; local_8 = local_8 + 1) {
    param_2[local_8 + 1] = *(undefined1 *)(param_1 + local_8 + 8);
  }
  return 10;
}

