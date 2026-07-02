// ============================================
// Address:  0x00698e30
// Original: FUN_00698e30
// Status:   unreviewed
// ============================================


void __fastcall FUN_00698e30(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069ff89;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006ad970;
  param_1[3] = &PTR_FUN_006aae18;
  param_1[4] = &PTR_LAB_006ad95c;
  local_8 = 3;
  FUN_006867e0();
  local_8._0_1_ = 2;
  FUN_00698430();
  local_8._0_1_ = 1;
  FUN_00699380();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0068dbb0();
  local_8 = 0xffffffff;
  FUN_00687ae0();
  ExceptionList = local_10;
  return;
}

