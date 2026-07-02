// ============================================
// Address:  0x00403d10
// Original: FUN_00403d10
// Status:   unreviewed
// ============================================


void __fastcall FUN_00403d10(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069da9a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a146c;
  local_8 = 0;
  FUN_00656200(param_1[2]);
  local_8 = 0xffffffff;
  FUN_004039d0();
  ExceptionList = local_10;
  return;
}

