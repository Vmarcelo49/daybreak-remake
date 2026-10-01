// Function: FUN_00661ea0
// Address:  0x00661ea0
// Source:   batch_decompile (mass dump)
// Hash:     c89822269f86ecf6


undefined4 FUN_00661ea0(undefined4 param_1,undefined4 param_2,int *param_3)

{
  void *pvVar1;
  undefined4 uVar2;
  int local_24;
  int local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f21b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_3 = 0;
  pvVar1 = operator_new(0xb0);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_00669a00();
  }
  local_8 = 0xffffffff;
  if (local_20 == 0) {
    uVar2 = 0x8007000e;
  }
  else {
    FUN_00669ac0(param_2);
    if (local_20 == 0) {
      local_24 = 0;
    }
    else {
      local_24 = local_20 + 0x10;
    }
    *param_3 = local_24;
    uVar2 = 0;
  }
  ExceptionList = local_10;
  return uVar2;
}

