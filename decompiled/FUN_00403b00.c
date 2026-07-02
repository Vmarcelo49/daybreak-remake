// Function: FUN_00403b00
// Address:  0x00403b00
// Source:   batch_decompile (mass dump)
// Hash:     14406c4c41294836


void __fastcall FUN_00403b00(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069da68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a142c;
  local_8 = 0;
  if (DAT_006cfce9 == '\x01') {
    FUN_00649620();
  }
  else {
    FUN_00648cf0();
  }
  local_8 = 0xffffffff;
  FUN_004039d0();
  ExceptionList = local_10;
  return;
}

