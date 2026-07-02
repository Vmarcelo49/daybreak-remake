// ============================================
// Address:  0x006983b0
// Original: FUN_006983b0
// Status:   unreviewed
// ============================================


undefined4 * __thiscall
FUN_006983b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  FUN_0068d8d0();
  FUN_006890c0(0,param_3,param_5,param_2,L"Output",1);
  *param_1 = &PTR_FUN_006ad930;
  param_1[2] = &PTR_FUN_006ad8f8;
  param_1[5] = &PTR_LAB_006ad8b0;
  param_1[6] = &PTR_LAB_006ad89c;
  param_1[0x28] = param_3;
  param_1[0x29] = param_4;
  return param_1;
}

