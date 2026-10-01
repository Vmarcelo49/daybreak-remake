// Function: FUN_0068cd50
// Address:  0x0068cd50
// Source:   batch_decompile (mass dump)
// Hash:     9716a8c0b0db855e


int FUN_0068cd50(int *param_1)

{
  int iVar1;
  int *local_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f7a0;
  local_10 = ExceptionList;
  if (param_1 == (int *)0xc) {
    local_2c = (int *)0x0;
  }
  else {
    local_2c = param_1 + 1;
  }
  ExceptionList = &local_10;
  FUN_0068d950(local_2c);
  local_8 = 0;
  if (param_1[0x11] == 0) {
    param_1[0x11] = 1;
    if (param_1[0x12] == 0) {
      iVar1 = (**(code **)(param_1[-3] + 0x14))();
      if (iVar1 < 0) {
        param_1[0x11] = 0;
        local_8 = 0xffffffff;
        FUN_0068d9a0();
      }
      else {
        (**(code **)(*param_1 + 4))(param_1);
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        iVar1 = 0;
      }
    }
    else {
      param_1[0x12] = 0;
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      iVar1 = 0;
    }
  }
  else {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    iVar1 = 0;
  }
  ExceptionList = local_10;
  return iVar1;
}

