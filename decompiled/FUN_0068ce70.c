// Function: FUN_0068ce70
// Address:  0x0068ce70
// Source:   batch_decompile (mass dump)
// Hash:     b9a81380ae503f2e


undefined4 FUN_0068ce70(int *param_1)

{
  int iVar1;
  int iVar2;
  int *local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f7b2;
  local_10 = ExceptionList;
  if (param_1 == (int *)0xc) {
    local_20 = (int *)0x0;
  }
  else {
    local_20 = param_1 + 1;
  }
  ExceptionList = &local_10;
  FUN_0068d950(local_20);
  local_8 = 0;
  if ((param_1[0x11] == 0) && (param_1[0x12] == 0)) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  else {
    param_1[0x11] = 0;
    iVar2 = FUN_0068dc80();
    iVar1 = param_1[0xc];
    if (iVar1 <= iVar2) {
      param_1[0x12] = 0;
      (**(code **)(param_1[-3] + 0x10))();
    }
    else {
      param_1[0x12] = 1;
    }
    FUN_0068cd10();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    if (iVar1 <= iVar2) {
      (**(code **)(*param_1 + 8))(param_1);
    }
  }
  ExceptionList = local_10;
  return 0;
}

