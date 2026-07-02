// ============================================
// Address:  0x00437100
// Original: FUN_00437100
// Status:   unreviewed
// ============================================


float * __thiscall FUN_00437100(float *param_1,float param_2)

{
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  return param_1;
}

