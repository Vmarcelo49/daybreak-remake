// Function: FUN_0065d430
// Address:  0x0065d430
// Source:   batch_decompile (mass dump)
// Hash:     6f0f10928c4c5adc


void FUN_0065d430(float param_1,float *param_2)

{
  *param_2 = (1.0 - param_1) * (1.0 - param_1) * (1.0 - param_1) * 0.16666667;
  param_2[1] = (param_1 * param_1 * param_1 * 0.5 - param_1 * param_1) + 0.6666667;
  param_2[2] = param_1 * 0.5 + param_1 * param_1 * 0.5 + param_1 * param_1 * param_1 * -0.5 +
               0.16666667;
  param_2[3] = param_1 * param_1 * param_1 * 0.16666667;
  return;
}

