// ============================================
// Address:  0x0042df10
// Original: FUN_0042df10
// Status:   unreviewed
// ============================================


float * __thiscall FUN_0042df10(float *param_1,float param_2)

{
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  param_1[2] = param_2 * param_1[2];
  return param_1;
}

