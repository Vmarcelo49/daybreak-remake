// Function: FUN_00689350
// Address:  0x00689350
// Source:   batch_decompile (mass dump)
// Hash:     8b418303edae005b


int FUN_00689350(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f5ad;
  local_10 = ExceptionList;
  if (param_2 == 0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x14));
    local_8 = 0;
    FUN_004176c0(param_2);
    if (*(int *)(param_1 + 0xc) == 0) {
      iVar1 = FUN_0068daa0();
      if ((iVar1 == 0) && (*(char *)(param_1 + 0x19) == '\0')) {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        iVar1 = -0x7ffbfddc;
      }
      else {
        iVar1 = FUN_006896b0(param_2,param_3);
        if (iVar1 < 0) {
          (**(code **)(*(int *)(param_1 + -0xc) + 0x2c))();
          local_8 = 0xffffffff;
          FUN_0068d9a0();
        }
        else {
          local_8 = 0xffffffff;
          FUN_0068d9a0();
          iVar1 = 0;
        }
      }
    }
    else {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      iVar1 = -0x7ffbfdfc;
    }
  }
  ExceptionList = local_10;
  return iVar1;
}

