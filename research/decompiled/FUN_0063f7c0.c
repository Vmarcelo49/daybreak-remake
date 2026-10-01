// Function: FUN_0063f7c0
// Address:  0x0063f7c0
// Source:   batch_decompile (mass dump)
// Hash:     5f66b0a86b42a168


int __thiscall FUN_0063f7c0(int param_1,undefined1 *param_2)

{
  int local_c;
  undefined2 *local_8;
  
  *param_2 = 0x2f;
  local_8 = (undefined2 *)(param_2 + 1);
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *local_8 = *(undefined2 *)(param_1 + 8 + local_c * 2);
    local_8 = local_8 + 1;
  }
  return (int)local_8 - (int)param_2;
}

