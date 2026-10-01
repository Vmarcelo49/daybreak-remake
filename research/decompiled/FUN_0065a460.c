// Function: FUN_0065a460
// Address:  0x0065a460
// Source:   batch_decompile (mass dump)
// Hash:     3a4712afb4c9243f


undefined4 __fastcall FUN_0065a460(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ef83;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0065a600();
  local_8 = 0;
  FUN_00653dc0();
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00653dc0();
  ExceptionList = local_10;
  return param_1;
}

