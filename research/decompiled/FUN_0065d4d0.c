// Function: FUN_0065d4d0
// Address:  0x0065d4d0
// Source:   batch_decompile (mass dump)
// Hash:     5f08aad7b38a73c2


void FUN_0065d4d0(float param_1,float *param_2)

{
  param_2[3] = (1.0 - param_1) * (1.0 - param_1) * (1.0 - param_1) * 0.25;
  param_2[2] = param_1 * 0.25 + (param_1 * param_1 * param_1 * 0.5833333 - param_1 * param_1 * 1.25)
               + 0.5833333;
  param_2[1] = param_1 * 0.5 + param_1 * param_1 * 0.5 + param_1 * param_1 * param_1 * -0.5 +
               0.16666667;
  *param_2 = param_1 * param_1 * param_1 * 0.16666667;
  return;
}

