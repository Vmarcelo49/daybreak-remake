// Function: FUN_00687ed0
// Address:  0x00687ed0
// Source:   batch_decompile (mass dump)
// Hash:     da4c7518afa3b834


int FUN_00687ed0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f4b0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1[0xb]);
  local_8 = 0;
  FUN_0068d8f0(param_2,param_3);
  if ((param_1[2] == 0) && (iVar1 = (**(code **)(*param_1 + 0x14))(param_1), iVar1 < 0)) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return iVar1;
  }
  if (param_1[2] != 2) {
    iVar1 = (**(code **)(param_1[-3] + 0x18))();
    for (local_20 = 0; local_20 < iVar1; local_20 = local_20 + 1) {
      piVar2 = (int *)(**(code **)(param_1[-3] + 0x1c))(local_20);
      iVar3 = FUN_0068da80();
      if ((iVar3 != 0) && (iVar3 = (**(code **)(*piVar2 + 0x1c))(param_2,param_3), iVar3 < 0)) {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        ExceptionList = local_10;
        return iVar3;
      }
    }
  }
  param_1[2] = 2;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

