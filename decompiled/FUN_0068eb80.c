// Function: FUN_0068eb80
// Address:  0x0068eb80
// Source:   batch_decompile (mass dump)
// Hash:     911e4d8994cc86d2


int FUN_0068eb80(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_30;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f91d;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x70);
  local_8 = 0;
  iVar1 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 8) == 2) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0068da80();
    if (iVar2 == 0) {
      if (param_1 == 0xc) {
        local_30 = 0;
      }
      else {
        local_30 = param_1;
      }
      FUN_006883f0(1,0,local_30);
      *(undefined4 *)(param_1 + 8) = 2;
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      iVar2 = 0;
    }
    else {
      FUN_00691bf0();
      iVar2 = FUN_00687ed0(param_1,param_2,param_3);
      if (iVar2 < 0) {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
      }
      else {
        (**(code **)(*(int *)(param_1 + -0xc) + 0x28))(1);
        FUN_0068fde0(0);
        iVar2 = FUN_00691b50();
        if (iVar2 != 0) {
          piVar3 = (int *)FUN_00691b50();
          (**(code **)(*piVar3 + 0x14))(piVar3);
        }
        if (iVar1 == 0) {
          *(undefined4 *)(param_1 + 0x54) = 0;
          (**(code **)(*(int *)(param_1 + -0xc) + 0x70))();
        }
        iVar2 = (**(code **)(*(int *)(param_1 + -0xc) + 0x7c))();
        local_8 = 0xffffffff;
        FUN_0068d9a0();
      }
    }
  }
  ExceptionList = local_10;
  return iVar2;
}

