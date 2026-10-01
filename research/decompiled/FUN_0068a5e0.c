// Function: FUN_0068a5e0
// Address:  0x0068a5e0
// Source:   batch_decompile (mass dump)
// Hash:     217b86cfa1fd5f9b


int FUN_0068a5e0(int param_1,undefined4 *param_2)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f61c;
  local_10 = ExceptionList;
  if (param_2 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + -0x78));
    local_8 = 0;
    if ((*(int *)(param_1 + 4) == 0) && (iVar1 = FUN_00687280(param_1 + 4), iVar1 < 0)) {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      ExceptionList = local_10;
      return iVar1;
    }
    *param_2 = *(undefined4 *)(param_1 + 4);
    (**(code **)(**(int **)(param_1 + 4) + 4))(*(undefined4 *)(param_1 + 4));
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    iVar1 = 0;
  }
  ExceptionList = local_10;
  return iVar1;
}

