// ============================================
// Address:  0x00694a30
// Original: FUN_00694a30
// Status:   unreviewed
// ============================================


undefined4 * __thiscall
FUN_00694a30(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,
            int param_5)

{
  FUN_0068d8d0();
  FUN_00694800(param_2,param_3);
  *param_1 = &PTR_FUN_006ad740;
  param_1[1] = &PTR_LAB_006ad7a8;
  param_1[2] = &PTR_FUN_006ad72c;
  param_1[6] = param_5;
  if (param_5 == 0) {
    *param_4 = 0x80004003;
  }
  return param_1;
}

