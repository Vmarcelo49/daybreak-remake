// ============================================
// Address:  0x0041b120
// Original: FUN_0041b120
// Status:   unreviewed
// ============================================


void __fastcall FUN_0041b120(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069e006;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a20b0;
  param_1[1] = &PTR_FUN_006a20a4;
  local_8 = 1;
  FUN_0065f780(0);
  FUN_00648cf0();
  local_8 = local_8 & 0xffffff00;
  FUN_00437230();
  local_8 = 0xffffffff;
  FUN_00403b00();
  ExceptionList = local_10;
  return;
}

