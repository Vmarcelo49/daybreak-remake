// ============================================
// Address:  0x0041d870
// Original: FUN_0041d870
// Status:   unreviewed
// ============================================


undefined4 * __fastcall FUN_0041d870(undefined4 *param_1)

{
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e13e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0040db80();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a240c;
  FUN_0065d610();
  local_8._0_1_ = 1;
  FUN_006572d0();
  local_8._0_1_ = 2;
  FUN_00424630();
  local_8._0_1_ = 3;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xb0));
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xb3));
  FUN_00424710();
  local_8._0_1_ = 4;
  FUN_00424710();
  local_8._0_1_ = 5;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xce));
  _vector_constructor_iterator_(param_1 + 0xe3,0x40,0xb,std::allocator<char>::allocator<char>);
  FUN_00433d30();
  local_8._0_1_ = 6;
  FUN_004247b0();
  local_8._0_1_ = 7;
  _eh_vector_constructor_iterator_(param_1 + 0x220,0x1c,1000,FUN_00423350,FUN_004232c0);
  local_8._0_1_ = 8;
  _eh_vector_constructor_iterator_(param_1 + 0x1d78,0x38,0x100,FUN_004231c0,FUN_00423270);
  local_8._0_1_ = 9;
  FUN_00431d30();
  local_8 = CONCAT31(local_8._1_3_,10);
  param_1[0x8f] = &DAT_006cafec;
  for (local_14 = 0; local_14 < 1000; local_14 = local_14 + 1) {
    FUN_004244c0();
  }
  for (local_18 = 0; local_18 < 0x100; local_18 = local_18 + 1) {
    FUN_00424210();
  }
  param_1[0x47] = 0;
  param_1[0x2bad] = 0;
  ExceptionList = local_10;
  return param_1;
}

