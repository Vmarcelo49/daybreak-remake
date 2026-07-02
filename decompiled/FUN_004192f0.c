// Function: FUN_004192f0
// Address:  0x004192f0
// Source:   batch_decompile (mass dump)
// Hash:     51ab3f4b3fca8371


void __thiscall FUN_004192f0(int param_1,undefined1 *param_2)

{
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  for (local_c = 0; local_8 = param_2 + 1, local_c < 8; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 8) = *local_8;
    param_2 = local_8;
  }
  for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
    *(undefined1 *)(param_1 + local_10 + 0x10) = *local_8;
    local_8 = local_8 + 1;
  }
  return;
}

