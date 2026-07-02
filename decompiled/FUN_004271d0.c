// Function: FUN_004271d0
// Address:  0x004271d0
// Source:   batch_decompile (mass dump)
// Hash:     8395bb0897062838


void FUN_004271d0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 3) {
    *param_1 = *param_3;
    param_1[1] = param_3[1];
    param_1[2] = param_3[2];
  }
  return;
}

