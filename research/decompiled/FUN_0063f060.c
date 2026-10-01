// Function: FUN_0063f060
// Address:  0x0063f060
// Source:   batch_decompile (mass dump)
// Hash:     f112e26d746e9314


void __thiscall FUN_0063f060(int param_1,int param_2)

{
  int local_c;
  undefined2 *local_8;
  
  local_8 = (undefined2 *)(param_2 + 1);
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined2 *)(param_1 + 8 + local_c * 2) = *local_8;
    local_8 = local_8 + 1;
  }
  return;
}

