// ============================================
// Address:  0x0068e9d0
// Original: FUN_0068e9d0
// Status:   unreviewed
// ============================================


int FUN_0068e9d0(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f90b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x70);
  local_8 = 0;
  iVar1 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 8) == 1) {
    iVar2 = (**(code **)(*(int *)(param_1 + -0xc) + 0x30))(1);
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  else {
    iVar2 = FUN_0068da80();
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 8) = 1;
      iVar2 = (**(code **)(*(int *)(param_1 + -0xc) + 0x30))(1);
      local_8 = 0xffffffff;
      FUN_0068d9a0();
    }
    else {
      iVar2 = FUN_00687de0(param_1);
      if (iVar2 < 0) {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
      }
      else {
        FUN_0068fde0(1);
        (**(code **)(*(int *)(param_1 + -0xc) + 0x80))();
        (**(code **)(*(int *)(param_1 + -0xc) + 0x28))(1);
        (**(code **)(*(int *)(param_1 + -0xc) + 0x6c))();
        FUN_0068fc20();
        iVar2 = FUN_00691b50();
        if (iVar2 != 0) {
          piVar3 = (int *)FUN_00691b50();
          (**(code **)(*piVar3 + 0x14))(piVar3);
        }
        if (iVar1 == 0) {
          *(undefined4 *)(param_1 + 0x54) = 0;
          (**(code **)(*(int *)(param_1 + -0xc) + 0x70))();
        }
        iVar2 = (**(code **)(*(int *)(param_1 + -0xc) + 0x30))(iVar1);
        local_8 = 0xffffffff;
        FUN_0068d9a0();
      }
    }
  }
  ExceptionList = local_10;
  return iVar2;
}

