// Function: FUN_006994c0
// Address:  0x006994c0
// Source:   batch_decompile (mass dump)
// Hash:     61c7ce2959fcd939


int __thiscall
FUN_006994c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  void *_Memory;
  int local_c;
  
  if ((param_5 == 0) ||
     (((iVar1 = FUN_00699f20(param_2,param_3), iVar1 != 0 &&
       (iVar1 = FUN_00698fd0(param_4), iVar1 != 0)) && (iVar1 = FUN_00698fd0(param_6), iVar1 != 0)))
     ) {
    _Memory = operator_new(0x28);
    if (_Memory == (void *)0x0) {
      local_c = -0x7ff8fff2;
    }
    else {
      local_c = FUN_00699110(param_1,*(undefined4 *)(param_1 + 0x18),param_2,param_3,param_4,param_5
                             ,param_6,param_7,param_8);
      if (-1 < local_c) {
        local_c = FUN_00699c00(_Memory);
      }
      if (local_c < 0) {
        _free(_Memory);
      }
    }
  }
  else {
    local_c = -0x7ffbfdf2;
  }
  return local_c;
}

