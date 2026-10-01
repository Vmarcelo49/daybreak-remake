// Function: FUN_0064d7a0
// Address:  0x0064d7a0
// Source:   batch_decompile (mass dump)
// Hash:     c605dff431dbd4e4


undefined4 * __fastcall FUN_0064d7a0(undefined4 *param_1)

{
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ebb1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0064efe0();
  local_8 = 0;
  FUN_0064efe0();
  local_8._0_1_ = 1;
  FUN_0064efe0();
  local_8 = CONCAT31(local_8._1_3_,2);
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x15));
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x17));
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  for (local_14 = 0; local_14 < 2; local_14 = local_14 + 1) {
    param_1[local_14 + 3] = 0;
  }
  FUN_00423890(param_1 + 0x17);
  FUN_0064ef00();
  FUN_0065a5e0();
  param_1[0x14] = 0x3f800000;
  param_1[0x11] = 0x3f800000;
  param_1[0x12] = 0x3f800000;
  param_1[0x13] = 0x3f800000;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  ExceptionList = local_10;
  return param_1;
}

