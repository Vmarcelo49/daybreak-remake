// ============================================
// Address:  0x0065ce10
// Original: FUN_0065ce10
// Status:   unreviewed
// ============================================


void __fastcall FUN_0065ce10(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069f0f8;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_0065d640(param_1);
  local_8 = 0xffffffff;
  FUN_0065cb40();
  ExceptionList = local_10;
  return;
}

