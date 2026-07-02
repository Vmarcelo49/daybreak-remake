// ============================================
// Address:  0x00658140
// Original: FUN_00658140
// Status:   unreviewed
// ============================================


int __fastcall FUN_00658140(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ee37;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006589e0();
  local_8 = 0;
  FUN_00658970();
  local_8._0_1_ = 1;
  FUN_006589e0();
  local_8 = CONCAT31(local_8._1_3_,2);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  FUN_0065a5e0();
  FUN_006589c0();
  FUN_0065a5e0();
  ExceptionList = local_10;
  return param_1;
}

