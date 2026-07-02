// ============================================
// Address:  0x00427f40
// Original: FUN_00427f40
// Status:   unreviewed
// ============================================


undefined4 * __thiscall FUN_00427f40(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[3] = param_2[3];
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  param_1[6] = param_2[6];
  param_1[7] = param_2[7];
  param_1[8] = param_2[8];
  param_1[9] = param_2[9];
  param_1[1] = param_2[1];
  param_1[10] = param_2[10];
  param_1[0xb] = param_2[0xb];
  _memcpy(param_1 + 0xc,param_2 + 0xc,0x14);
  return param_1;
}

