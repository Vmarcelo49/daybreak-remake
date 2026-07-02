// Function: FUN_00687700
// Address:  0x00687700
// Source:   batch_decompile (mass dump)
// Hash:     5147b1164c7eb2aa


int FUN_00687700(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f420;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1[9]);
  local_8 = 0;
  FUN_0068d8f0(param_2,param_3);
  if ((param_1[1] == 0) && (iVar1 = (**(code **)(*param_1 + 0x14))(param_1), iVar1 < 0)) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return iVar1;
  }
  param_1[1] = 2;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

