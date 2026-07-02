// ============================================
// Address:  0x00688120
// Original: FUN_00688120
// Status:   unreviewed
// ============================================


undefined4 FUN_00688120(int param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int local_2c;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f4d7;
  local_10 = ExceptionList;
  if (param_3 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x2c));
    local_8 = 0;
    iVar2 = (**(code **)(*(int *)(param_1 + -0xc) + 0x18))();
    for (local_1c = 0; local_1c < iVar2; local_1c = local_1c + 1) {
      iVar3 = (**(code **)(*(int *)(param_1 + -0xc) + 0x1c))(local_1c);
      uVar1 = param_2;
      uVar4 = FUN_0068dac0(param_2);
      iVar5 = FUN_006924c0(uVar4,uVar1);
      if (iVar5 == 0) {
        if (iVar3 == 0) {
          local_2c = 0;
        }
        else {
          local_2c = iVar3 + 0xc;
        }
        *param_3 = local_2c;
        (**(code **)(*(int *)(iVar3 + 0xc) + 4))(iVar3 + 0xc);
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        ExceptionList = local_10;
        return 0;
      }
    }
    *param_3 = 0;
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0x80040216;
  }
  ExceptionList = local_10;
  return uVar1;
}

