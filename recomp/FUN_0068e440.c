// ============================================
// Address:  0x0068e440
// Original: FUN_0068e440
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068e440(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  void *pvVar2;
  int *piVar3;
  int local_48;
  int local_44;
  int local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f8e7;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x31);
  local_8 = 0;
  if (param_1[0x14] == 0) {
    local_18[0] = 0;
    pvVar2 = operator_new(0x50);
    local_8._0_1_ = 1;
    if (pvVar2 == (void *)0x0) {
      local_48 = 0;
    }
    else {
      local_44 = (**(code **)(*param_1 + 0x1c))(0);
      if (local_44 == 0) {
        local_44 = 0;
      }
      else {
        local_44 = local_44 + 0xc;
      }
      piVar3 = local_18;
      uVar1 = FUN_0068dc80(piVar3,local_44);
      local_48 = FUN_006954d0(0,uVar1,piVar3,local_44);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x14] = local_48;
    if (param_1[0x14] == 0) {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar1 = 0x8007000e;
    }
    else if (local_18[0] < 0) {
      if (param_1[0x14] == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = (**(code **)(*(int *)(param_1[0x14] + 8) + 0xc))(1);
      }
      param_1[0x14] = 0;
      local_8 = 0xffffffff;
      FUN_0068d9a0(uVar1);
      uVar1 = 0x80004002;
    }
    else {
      uVar1 = (**(code **)(*param_1 + 0x24))(param_2,param_3);
      local_8 = 0xffffffff;
      FUN_0068d9a0();
    }
  }
  else {
    uVar1 = (*(code *)**(undefined4 **)(param_1[0x14] + 8))(param_1[0x14] + 8,param_2,param_3);
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  ExceptionList = local_10;
  return uVar1;
}

