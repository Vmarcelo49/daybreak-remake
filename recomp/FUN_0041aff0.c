// ============================================
// Address:  0x0041aff0
// Original: FUN_0041aff0
// Status:   unreviewed
// ============================================


undefined4 * __fastcall FUN_0041aff0(undefined4 *param_1)

{
  undefined4 *local_1c;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dfe6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403ae0();
  local_8 = 0;
  FUN_0041af50();
  *param_1 = &PTR_FUN_006a20b0;
  param_1[1] = &PTR_FUN_006a20a4;
  FUN_00417750();
  FUN_004248f0();
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00415da0();
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    FUN_0040da90();
    FUN_00657850();
    *(undefined2 *)(&DAT_006cb758 + local_14 * 0xc) = 0xffff;
  }
  param_1[0x4a] = 1;
  FUN_00437230();
  if (param_1 == (undefined4 *)0x0) {
    local_1c = (undefined4 *)0x0;
  }
  else {
    local_1c = param_1 + 1;
  }
  FUN_0065f780(local_1c);
  ExceptionList = local_10;
  return param_1;
}

