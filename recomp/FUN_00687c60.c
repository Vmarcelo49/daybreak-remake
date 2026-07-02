// ============================================
// Address:  0x00687c60
// Original: FUN_00687c60
// Status:   unreviewed
// ============================================


undefined4 FUN_00687c60(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f47a;
  local_10 = ExceptionList;
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x2c));
    local_8 = 0;
    if (*(int *)(param_1 + 0xc) != 0) {
      (**(code **)(**(int **)(param_1 + 0xc) + 4))(*(undefined4 *)(param_1 + 0xc));
    }
    *param_2 = *(undefined4 *)(param_1 + 0xc);
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0;
  }
  ExceptionList = local_10;
  return uVar1;
}

