// Function: FUN_0068f460
// Address:  0x0068f460
// Source:   batch_decompile (mass dump)
// Hash:     7016146fea6d72e8


int __thiscall FUN_0068f460(int *param_1,int param_2)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f966;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x1f);
  local_8 = 0;
  param_1[0x2d] = 1;
  iVar1 = FUN_0068a7b0(param_1[0x1e] + 0x98,param_2);
  if (iVar1 == 0) {
    iVar1 = FUN_00691ad0();
    if (*(int *)(iVar1 + 0x24) != 0) {
      iVar1 = FUN_00691ad0();
      iVar1 = (**(code **)(*(int *)param_1[0x1e] + 0x24))(*(undefined4 *)(iVar1 + 0x24));
      if (iVar1 < 0) {
        param_1[0x2d] = 0;
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        ExceptionList = local_10;
        return iVar1;
      }
    }
    FUN_0068d950(param_1 + 0x25);
    local_8._0_1_ = 1;
    if (((param_1[0x1b] == 0) && (param_1[0x1c] == 0)) && (param_1[0x18] == 0)) {
      if (param_1[0x14] != 0) {
        FUN_00695580(param_2);
      }
      if ((param_1[0x19] == 1) && (iVar1 = (**(code **)(*param_1 + 0x54))(param_2), iVar1 == 0)) {
        param_1[0x2d] = 0;
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_0068d9a0();
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        ExceptionList = local_10;
        return -0x7ffbfdd5;
      }
      iVar1 = FUN_00691ad0();
      param_1[0x2e] = *(int *)(iVar1 + 0x18);
      param_1[0x2f] = *(int *)(iVar1 + 0x1c);
      param_1[0x1b] = param_2;
      (**(code **)(*(int *)param_1[0x1b] + 4))(param_1[0x1b]);
      if (param_1[0x19] == 0) {
        FUN_0068fde0(1);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_0068d9a0();
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      iVar1 = 0;
    }
    else {
      FUN_00691bf0();
      param_1[0x2d] = 0;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_0068d9a0();
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      iVar1 = -0x7fff0001;
    }
  }
  else {
    param_1[0x2d] = 0;
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    iVar1 = -0x7fffbffb;
  }
  ExceptionList = local_10;
  return iVar1;
}

