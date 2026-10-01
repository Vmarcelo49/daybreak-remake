// Function: FUN_00691eb0
// Address:  0x00691eb0
// Source:   batch_decompile (mass dump)
// Hash:     daea93bb7de1e671


void __fastcall FUN_00691eb0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069fb17;
  local_10 = ExceptionList;
  local_8 = 3;
  ExceptionList = &local_10;
  FUN_00693370(param_1);
  local_8._0_1_ = 2;
  FUN_0068dbb0();
  local_8._0_1_ = 1;
  FUN_0068dbb0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00691d70();
  local_8 = 0xffffffff;
  FUN_00691d70();
  ExceptionList = local_10;
  return;
}

