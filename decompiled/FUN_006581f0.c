// Function: FUN_006581f0
// Address:  0x006581f0
// Source:   batch_decompile (mass dump)
// Hash:     02777a08420fca7c


void __fastcall FUN_006581f0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069ee68;
  local_10 = ExceptionList;
  local_8 = 2;
  ExceptionList = &local_10;
  FUN_006582d0(param_1);
  local_8._0_1_ = 1;
  FUN_0065a5e0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006589c0();
  local_8 = 0xffffffff;
  FUN_0065a5e0();
  ExceptionList = local_10;
  return;
}

