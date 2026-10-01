// Function: FUN_0064fcd0
// Address:  0x0064fcd0
// Source:   batch_decompile (mass dump)
// Hash:     683612bec9600c06


undefined4 * FUN_0064fcd0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  while (param_1 != param_2) {
    param_2 = param_2 + -1;
    param_3 = param_3 + -1;
    *param_3 = *param_2;
  }
  return param_3;
}

