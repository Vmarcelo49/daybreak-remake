// ============================================
// Address:  0x00697830
// Original: FUN_00697830
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00697830(int param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fe3b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 8);
  local_8 = 0;
  FUN_0068d8f0(param_2,param_3);
  *(undefined4 *)(param_1 + 100) = 1;
  FUN_00697630();
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

