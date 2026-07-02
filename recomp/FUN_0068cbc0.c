// ============================================
// Address:  0x0068cbc0
// Original: FUN_0068cbc0
// Status:   unreviewed
// ============================================


undefined4 FUN_0068cbc0(int param_1,int *param_2)

{
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f77c;
  local_10 = ExceptionList;
  if (param_1 == 0xc) {
    local_1c = 0;
  }
  else {
    local_1c = param_1 + 4;
  }
  ExceptionList = &local_10;
  FUN_0068d950(local_1c);
  local_8 = 0;
  if (param_2 != (int *)0x0) {
    (**(code **)(*param_2 + 4))(param_2);
  }
  if (*(int *)(param_1 + 0x4c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x4c) + 8))(*(undefined4 *)(param_1 + 0x4c));
  }
  *(int **)(param_1 + 0x4c) = param_2;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

