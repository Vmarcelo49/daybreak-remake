// Function: FUN_006956a0
// Address:  0x006956a0
// Source:   batch_decompile (mass dump)
// Hash:     c087f8628de6be4d


int __thiscall FUN_006956a0(int *param_1,undefined4 param_2,int param_3)

{
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fc70;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 7);
  local_8 = 0;
  if (param_1[0x12] == 1) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    local_14 = -0x7fffbffb;
  }
  else {
    local_14 = (**(code **)(*param_1 + 0x34))
                         (param_1,param_2,0,param_1[0xe],param_1[0xf],&DAT_006ad154);
    if ((param_3 != 0) && (-1 < local_14)) {
      local_14 = (**(code **)(*param_1 + 0x34))
                           (param_1,param_3,0,param_1[0x10],param_1[0x11],&DAT_006ad154);
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  ExceptionList = local_10;
  return local_14;
}

