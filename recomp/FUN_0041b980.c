// ============================================
// Address:  0x0041b980
// Original: FUN_0041b980
// Status:   unreviewed
// ============================================


undefined4 * __fastcall FUN_0041b980(undefined4 *param_1)

{
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e018;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00408330();
  local_8 = 0;
  FUN_0041af50();
  *param_1 = &PTR_FUN_006a2188;
  param_1[0xf66] = &PTR_FUN_006a217c;
  FUN_00418c10();
  FUN_00418f70();
  FUN_00419170();
  FUN_00417750();
  FUN_00419240();
  FUN_00415da0();
  param_1[0xff3] = 0;
  if (param_1 == (undefined4 *)0x0) {
    local_18 = (undefined4 *)0x0;
  }
  else {
    local_18 = param_1 + 0xf66;
  }
  FUN_0065f780(local_18);
  ExceptionList = local_10;
  return param_1;
}

