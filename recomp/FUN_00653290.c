// ============================================
// Address:  0x00653290
// Original: FUN_00653290
// Status:   unreviewed
// ============================================


void __fastcall FUN_00653290(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069eca1;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  FUN_00424670(param_1);
  local_8 = local_8 & 0xffffff00;
  FUN_00653c70();
  local_8 = 0xffffffff;
  FUN_00653bb0();
  ExceptionList = local_10;
  return;
}

