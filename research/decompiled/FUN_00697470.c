// Function: FUN_00697470
// Address:  0x00697470
// Source:   batch_decompile (mass dump)
// Hash:     a0a8cd571541c71a


undefined4 __thiscall FUN_00697470(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_20;
  undefined4 local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fe17;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 8);
  local_8 = 0;
  local_1c = 0;
  iVar2 = FUN_00698070();
  if (iVar2 == 0) {
    local_18 = param_1 + 0x20;
  }
  else {
    local_18 = param_1 + 0x38;
  }
  local_20 = FUN_0068de10();
  while (local_20 != 0) {
    iVar2 = FUN_006981f0(local_20);
    if (iVar2 == param_2) break;
    FUN_006981d0(&local_20);
  }
  if (local_20 == 0) {
    local_1c = 0x80040216;
  }
  else {
    FUN_00698210(local_20);
    (**(code **)(*(int *)(param_2 + 0xc) + 8))(param_2 + 0xc);
    FUN_00697630();
  }
  uVar1 = local_1c;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return uVar1;
}

