// ============================================
// Address:  0x00633a60
// Original: FUN_00633a60
// Status:   unreviewed
// ============================================


float * __thiscall FUN_00633a60(float *param_1,float *param_2)

{
  *param_1 = *param_1 - *param_2;
  param_1[1] = param_1[1] - param_2[1];
  param_1[2] = param_1[2] - param_2[2];
  return param_1;
}

