// ============================================
// Address:  0x004234c0
// Original: FUN_004234c0
// Status:   unreviewed
// ============================================


void __fastcall FUN_004234c0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e2ab;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00424350(param_1);
  local_8 = 0xffffffff;
  FUN_00424350();
  ExceptionList = local_10;
  return;
}

