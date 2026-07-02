// ============================================
// Address:  0x0068c9a0
// Original: FUN_0068c9a0
// Status:   unreviewed
// ============================================


undefined4 FUN_0068c9a0(int param_1,int *param_2,undefined4 param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  int local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f758;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_2 = 0;
  while( true ) {
    if (param_1 == 0xc) {
      local_20 = 0;
    }
    else {
      local_20 = param_1 + 4;
    }
    FUN_0068d950(local_20);
    local_8 = 0;
    if (*(int *)(param_1 + 0x44) == 0) {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      ExceptionList = local_10;
      return 0x80040211;
    }
    iVar1 = FUN_0068dca0();
    if (iVar1 == 0) {
      FUN_0068dcf0();
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    if (iVar1 != 0) break;
    if ((param_5 & 4) != 0) {
      ExceptionList = local_10;
      return 0x8004022e;
    }
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x24),0xffffffff);
  }
  *(undefined4 *)(iVar1 + 0x44) = 1;
  *param_2 = iVar1;
  ExceptionList = local_10;
  return 0;
}

