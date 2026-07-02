// Function: FUN_00668aa0
// Address:  0x00668aa0
// Source:   batch_decompile (mass dump)
// Hash:     a2735449a800a2bd


undefined4 * __thiscall FUN_00668aa0(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)

{
  FUN_00690650(&DAT_006ab35c,0,param_2,param_3);
  *param_1 = &PTR_FUN_006ab298;
  param_1[3] = &PTR_FUN_006ab258;
  param_1[4] = &PTR_LAB_006ad95c;
  param_1[0x38] = &PTR_LAB_006ab234;
  param_1[0x39] = &PTR_LAB_006ad5f4;
  param_1[0x5b] = 0;
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
  }
  *(undefined1 *)(param_1 + 0x5a) = 0;
  return param_1;
}

