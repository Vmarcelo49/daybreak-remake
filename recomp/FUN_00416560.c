// ============================================
// Address:  0x00416560
// Original: FUN_00416560
// Status:   unreviewed
// ============================================


void __thiscall FUN_00416560(int param_1,int param_2)

{
  undefined4 local_c;
  
  for (local_c = 0; local_c < 9; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 8) = *(undefined1 *)(param_2 + 1 + local_c);
  }
  return;
}

