// ============================================
// Address:  0x0063f4c0
// Original: FUN_0063f4c0
// Status:   unreviewed
// ============================================


undefined1 * __thiscall FUN_0063f4c0(int param_1,undefined1 *param_2)

{
  int local_c;
  undefined2 *local_8;
  
  *param_2 = 0x1c;
  local_8 = (undefined2 *)(param_2 + 1);
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *local_8 = *(undefined2 *)(param_1 + 8 + local_c * 4);
    local_8 = local_8 + 1;
  }
  *local_8 = *(undefined2 *)(param_1 + 0x18);
  return (undefined1 *)((int)local_8 + (2 - (int)param_2));
}

