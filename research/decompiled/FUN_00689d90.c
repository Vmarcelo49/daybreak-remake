// Function: FUN_00689d90
// Address:  0x00689d90
// Source:   batch_decompile (mass dump)
// Hash:     c6da6864a964d44e


undefined4 FUN_00689d90(int param_1,int *param_2)

{
  undefined4 uVar1;
  void *pvVar2;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f5f8;
  local_10 = ExceptionList;
  if (param_2 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    pvVar2 = operator_new(0x14);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00688be0(param_1 + -0xc,0);
    }
    *param_2 = local_1c;
    if (*param_2 == 0) {
      uVar1 = 0x8007000e;
    }
    else {
      uVar1 = 0;
    }
  }
  ExceptionList = local_10;
  return uVar1;
}

