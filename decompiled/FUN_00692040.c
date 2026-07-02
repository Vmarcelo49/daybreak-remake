// Function: FUN_00692040
// Address:  0x00692040
// Source:   batch_decompile (mass dump)
// Hash:     fe8ec7fa8e99f34c


undefined4 __thiscall FUN_00692040(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fb3b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x18);
  local_8 = 0;
  iVar1 = FUN_006933b0();
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar2 = 0x80004005;
  }
  else {
    *(undefined4 *)(param_1 + 0xc) = param_2;
    FUN_006919a0();
    FUN_00693320(0xffffffff);
    uVar2 = *(undefined4 *)(param_1 + 0x10);
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  ExceptionList = local_10;
  return uVar2;
}

