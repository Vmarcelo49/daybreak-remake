// ============================================
// Address:  0x00404f90
// Original: FUN_00404f90
// Status:   unreviewed
// ============================================


void __fastcall FUN_00404f90(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069dafa;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a14ec;
  local_8 = 0;
  FUN_0065bea0();
  local_8 = 0xffffffff;
  FUN_004039d0();
  ExceptionList = local_10;
  return;
}

