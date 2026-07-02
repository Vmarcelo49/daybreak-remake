// Function: FUN_006900f0
// Address:  0x006900f0
// Source:   batch_decompile (mass dump)
// Hash:     f9eca46ca29984ea


int FUN_006900f0(int param_1)

{
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fa28;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(*(int *)(param_1 + 0xcc) + 0x7c);
  local_8 = 0;
  FUN_0068d950(*(int *)(param_1 + 0xcc) + 0x94);
  local_8._0_1_ = 1;
  local_1c = (**(code **)(*(int *)(param_1 + -0xc) + 0x38))();
  if (local_1c == 0) {
    local_1c = (**(code **)(**(int **)(param_1 + 0xcc) + 0x68))();
    if (-1 < local_1c) {
      local_1c = FUN_00689ed0(param_1);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_0068d9a0();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  else {
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_0068d9a0();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  ExceptionList = local_10;
  return local_1c;
}

