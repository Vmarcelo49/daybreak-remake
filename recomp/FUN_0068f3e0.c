// ============================================
// Address:  0x0068f3e0
// Original: FUN_0068f3e0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0068f3e0(int param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f94c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x94);
  local_8 = 0;
  if (*(int *)(param_1 + 0x6c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x6c) + 4))(*(undefined4 *)(param_1 + 0x6c));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x6c);
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return uVar1;
}

