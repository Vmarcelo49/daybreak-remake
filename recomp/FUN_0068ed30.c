// ============================================
// Address:  0x0068ed30
// Original: FUN_0068ed30
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068ed30(int param_1,int param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 local_40;
  int local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f93a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0xc4);
  local_8 = 0;
  if (param_2 != 0) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0;
  }
  if (*(int *)(param_1 + 0x78) == 0) {
    local_18[0] = 0;
    pvVar1 = operator_new(0xe0);
    local_8._0_1_ = 1;
    if (pvVar1 == (void *)0x0) {
      local_40 = 0;
    }
    else {
      local_40 = FUN_00690080(param_1,local_18,&DAT_006ad42c);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    *(undefined4 *)(param_1 + 0x78) = local_40;
    if (*(int *)(param_1 + 0x78) == 0) {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      ExceptionList = local_10;
      return 0;
    }
    if (local_18[0] < 0) {
      if (*(int **)(param_1 + 0x78) == (int *)0x0) {
        uVar2 = 0;
      }
      else {
        uVar2 = (**(code **)(**(int **)(param_1 + 0x78) + 0xc))(1);
      }
      *(undefined4 *)(param_1 + 0x78) = 0;
      local_8 = 0xffffffff;
      FUN_0068d9a0(uVar2);
      ExceptionList = local_10;
      return 0;
    }
  }
  uVar2 = *(undefined4 *)(param_1 + 0x78);
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return uVar2;
}

