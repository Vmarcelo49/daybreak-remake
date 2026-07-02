// ============================================
// Address:  0x006901e0
// Original: FUN_006901e0
// Status:   unreviewed
// ============================================


undefined4 FUN_006901e0(int param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fa42;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(*(int *)(param_1 + 0xcc) + 0x7c);
  local_8 = 0;
  FUN_0068d950(*(int *)(param_1 + 0xcc) + 0x94);
  local_8._0_1_ = 1;
  FUN_0068ab50(param_1);
  (**(code **)(**(int **)(param_1 + 0xcc) + 0x84))();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0068d9a0();
  uVar1 = (**(code **)(**(int **)(param_1 + 0xcc) + 100))();
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return uVar1;
}

