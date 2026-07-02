// ============================================
// Address:  0x0068a6a0
// Original: FUN_0068a6a0
// Status:   unreviewed
// ============================================


undefined4 FUN_0068a6a0(int param_1,int *param_2,undefined1 param_3)

{
  int *piVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f62e;
  local_10 = ExceptionList;
  if (param_2 == (int *)0x0) {
    uVar2 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + -0x78));
    local_8 = 0;
    piVar1 = *(int **)(param_1 + 4);
    (**(code **)(*param_2 + 4))(param_2);
    *(int **)(param_1 + 4) = param_2;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
    }
    *(undefined1 *)(param_1 + 8) = param_3;
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar2 = 0;
  }
  ExceptionList = local_10;
  return uVar2;
}

