// Function: FUN_0064c600
// Address:  0x0064c600
// Source:   batch_decompile (mass dump)
// Hash:     62c724f21d79bfda


void __fastcall FUN_0064c600(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069eb82;
  local_10 = ExceptionList;
  local_8 = 3;
  ExceptionList = &local_10;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x44b8),0x160,4,FUN_00632cc0);
  local_8._0_1_ = 2;
  FUN_0063bf80();
  local_8._0_1_ = 1;
  FUN_0063bf60();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00437230();
  local_8 = 0xffffffff;
  FUN_0065d640();
  ExceptionList = local_10;
  return;
}

