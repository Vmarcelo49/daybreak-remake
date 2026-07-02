// ============================================
// Address:  0x00427060
// Original: FUN_00427060
// Status:   unreviewed
// ============================================


void FUN_00427060(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e351;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00410cf0(0x18,param_1);
  local_8 = 0;
  if (iVar1 != 0) {
    <>(param_2);
  }
  ExceptionList = local_10;
  return;
}

