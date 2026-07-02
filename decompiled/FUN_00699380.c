// Function: FUN_00699380
// Address:  0x00699380
// Source:   batch_decompile (mass dump)
// Hash:     949938f41162c6aa


void __fastcall FUN_00699380(undefined4 param_1)

{
  void *_Memory;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_006a0049;
  local_10 = ExceptionList;
  local_8 = 7;
  ExceptionList = &local_10;
  FUN_00699820(param_1);
  FUN_00699a70();
  local_14 = FUN_0068de10();
  while (local_14 != 0) {
    _Memory = (void *)FUN_006981d0(&local_14);
    _free(_Memory);
  }
  FUN_00693630();
  local_8._0_1_ = 6;
  FUN_00691d70();
  local_8._0_1_ = 5;
  FUN_00691d70();
  local_8._0_1_ = 4;
  FUN_00691d70();
  local_8._0_1_ = 3;
  FUN_00691d70();
  local_8._0_1_ = 2;
  FUN_00693440();
  local_8._0_1_ = 1;
  FUN_00693440();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0068dbb0();
  local_8 = 0xffffffff;
  FUN_0068dbb0();
  ExceptionList = local_10;
  return;
}

