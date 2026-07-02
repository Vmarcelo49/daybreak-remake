// Function: FUN_006978c0
// Address:  0x006978c0
// Source:   batch_decompile (mass dump)
// Hash:     dc954097e744b3e4


undefined4 __fastcall FUN_006978c0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fe4d;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 8);
  local_8 = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  FUN_00697630();
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

