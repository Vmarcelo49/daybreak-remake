// Function: FUN_0068fc60
// Address:  0x0068fc60
// Source:   batch_decompile (mass dump)
// Hash:     5a89151e9e6bc50f


undefined4 __fastcall FUN_0068fc60(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f9d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x25);
  local_8 = 0;
  if (param_1[0x19] == 1) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0;
  }
  else {
    param_1[0x19] = 1;
    timeBeginPeriod(1);
    (**(code **)(*param_1 + 0x40))();
    if (param_1[0x1b] == 0) {
      uVar1 = (**(code **)(*param_1 + 0x60))();
      local_8 = 0xffffffff;
      FUN_0068d9a0();
    }
    else {
      iVar2 = (**(code **)(*param_1 + 0x54))(param_1[0x1b]);
      if (iVar2 == 0) {
        FUN_006919a0();
      }
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar1 = 0;
    }
  }
  ExceptionList = local_10;
  return uVar1;
}

