// Function: FUN_0063be70
// Address:  0x0063be70
// Source:   batch_decompile (mass dump)
// Hash:     6a32f2afad2d1c99


float * __thiscall FUN_0063be70(float *param_1,float param_2)

{
  param_2 = 1.0 / param_2;
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  param_1[2] = param_2 * param_1[2];
  return param_1;
}

