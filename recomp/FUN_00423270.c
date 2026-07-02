// ============================================
// Address:  0x00423270
// Original: FUN_00423270
// Status:   unreviewed
// ============================================


void __fastcall FUN_00423270(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e26b;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00424210(param_1);
  local_8 = 0xffffffff;
  FUN_00424210();
  ExceptionList = local_10;
  return;
}

