// Function: FUN_00687cf0
// Address:  0x00687cf0
// Source:   batch_decompile (mass dump)
// Hash:     59fbd2d63047ac75


int FUN_00687cf0(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_20;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f48c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(*(undefined4 *)(param_1 + 0x2c));
  local_8 = 0;
  local_18 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    iVar1 = (**(code **)(*(int *)(param_1 + -0xc) + 0x18))();
    for (local_20 = 0; local_20 < iVar1; local_20 = local_20 + 1) {
      piVar2 = (int *)(**(code **)(*(int *)(param_1 + -0xc) + 0x1c))(local_20);
      iVar3 = FUN_0068da80();
      if (iVar3 != 0) {
        iVar3 = (**(code **)(*piVar2 + 0x18))();
        if ((iVar3 < 0) && (-1 < local_18)) {
          local_18 = iVar3;
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 8) = 0;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return local_18;
}

