// Function: FUN_0068c1a0
// Address:  0x0068c1a0
// Source:   batch_decompile (mass dump)
// Hash:     5504da60ee6380f5


int __thiscall FUN_0068c1a0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  allocator<char> local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f6de;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_0068da80();
  if (iVar1 == 0) {
    iVar1 = -0x7ffbfdf7;
  }
  else {
    FUN_00425ac0();
    local_8 = 0;
    uVar2 = std::allocator<char>::allocator<char>(local_14);
    (**(code **)**(undefined4 **)(param_1 + 0x18))
              (*(undefined4 *)(param_1 + 0x18),&DAT_006acf64,uVar2);
    iVar1 = FUN_0068de10();
    if (iVar1 != 0) {
      piVar3 = (int *)FUN_0068de10();
      iVar1 = (**(code **)(*piVar3 + 0xc))(piVar3,param_2);
      if (iVar1 == 0) {
        iVar1 = FUN_0068c2b0(param_2);
        if (iVar1 < 0) {
          local_8 = 0xffffffff;
          FUN_0068dde0();
          ExceptionList = local_10;
          return iVar1;
        }
        local_8 = 0xffffffff;
        FUN_0068dde0();
        ExceptionList = local_10;
        return 0;
      }
    }
    iVar1 = FUN_0068c430(param_2);
    local_8 = 0xffffffff;
    FUN_0068dde0();
  }
  ExceptionList = local_10;
  return iVar1;
}

