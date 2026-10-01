// Function: FUN_0065d580
// Address:  0x0065d580
// Source:   batch_decompile (mass dump)
// Hash:     caf4402e89178992


void FUN_0065d580(float param_1,float *param_2)

{
  param_2[3] = (1.0 - param_1) * (1.0 - param_1) * (1.0 - param_1);
  param_2[2] = param_1 * 3.0 + (param_1 * param_1 * param_1 * 1.75 - param_1 * param_1 * 4.5);
  param_2[1] = param_1 * param_1 * 1.5 + param_1 * param_1 * -0.9166667;
  *param_2 = param_1 * param_1 * param_1 * 0.16666667;
  return;
}

