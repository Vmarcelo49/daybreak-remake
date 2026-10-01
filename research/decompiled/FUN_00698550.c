// Function: FUN_00698550
// Address:  0x00698550
// Source:   batch_decompile (mass dump)
// Hash:     decb0b26f944f0cb


undefined4 __thiscall FUN_00698550(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ff08;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(*(undefined4 *)(param_1 + 0x20));
  local_8 = 0;
  iVar2 = param_2;
  uVar1 = FUN_00698fb0(param_2);
  iVar2 = FUN_006871b0(uVar1,iVar2);
  if (iVar2 == 0) {
LAB_006985fd:
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 1;
  }
  else {
    puVar3 = &DAT_006ad998;
    iVar2 = FUN_00698fb0(&DAT_006ad998);
    iVar2 = FUN_006871b0(iVar2 + 0x10,puVar3);
    if (iVar2 == 0) {
      param_2 = param_2 + 0x10;
      iVar2 = FUN_00698fb0(param_2);
      iVar2 = FUN_006871b0(iVar2 + 0x10,param_2);
      if (iVar2 == 0) goto LAB_006985fd;
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0;
  }
  ExceptionList = local_10;
  return uVar1;
}

