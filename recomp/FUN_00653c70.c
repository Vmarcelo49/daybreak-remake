// ============================================
// Address:  0x00653c70
// Original: FUN_00653c70
// Status:   unreviewed
// ============================================


void __fastcall FUN_00653c70(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069ecf3;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  FUN_0065a5e0(param_1);
  local_8 = local_8 & 0xffffff00;
  FUN_0065a5e0();
  local_8 = 0xffffffff;
  FUN_0065a5e0();
  ExceptionList = local_10;
  return;
}

