// Function: FUN_0042df10
// Address:  0x0042df10
// Source:   batch_decompile (mass dump)
// Hash:     0f30dbb8537cfba0


float * __thiscall FUN_0042df10(float *param_1,float param_2)

{
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  param_1[2] = param_2 * param_1[2];
  return param_1;
}

