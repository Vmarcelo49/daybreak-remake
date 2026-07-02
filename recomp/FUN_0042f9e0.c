// ============================================
// Address:  0x0042f9e0
// Original: FUN_0042f9e0
// Status:   unreviewed
// ============================================


void __fastcall FUN_0042f9e0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069e446;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a2570;
  local_8 = 1;
  FUN_0042fa80();
  local_8 = local_8 & 0xffffff00;
  FUN_0065d640();
  local_8 = 0xffffffff;
  FUN_00424670();
  ExceptionList = local_10;
  return;
}

