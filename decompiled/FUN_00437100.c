// Function: FUN_00437100
// Address:  0x00437100
// Source:   batch_decompile (mass dump)
// Hash:     68c58021a140067d


float * __thiscall FUN_00437100(float *param_1,float param_2)

{
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  return param_1;
}

