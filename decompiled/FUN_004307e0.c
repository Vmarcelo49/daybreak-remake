// Function: FUN_004307e0
// Address:  0x004307e0
// Source:   batch_decompile (mass dump)
// Hash:     2fff1f7d4f012fca


float * __thiscall FUN_004307e0(float *param_1,float param_2)

{
  param_2 = 1.0 / param_2;
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  param_1[2] = param_2 * param_1[2];
  param_1[3] = param_2 * param_1[3];
  return param_1;
}

