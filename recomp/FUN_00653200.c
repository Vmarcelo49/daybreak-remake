// ============================================
// Address:  0x00653200
// Original: FUN_00653200
// Status:   unreviewed
// ============================================


int __fastcall FUN_00653200(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ec81;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00653b50();
  local_8 = 0;
  FUN_00653c10();
  local_8._0_1_ = 1;
  FUN_00653cd0();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004248b0();
  FUN_004248b0();
  *(undefined4 *)(param_1 + 0x7c) = 0;
  ExceptionList = local_10;
  return param_1;
}

