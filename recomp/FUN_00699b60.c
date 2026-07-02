// ============================================
// Address:  0x00699b60
// Original: FUN_00699b60
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00699b60(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_006a00ab;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x1c);
  local_8 = 0;
  uVar1 = FUN_00693460();
  iVar2 = FUN_00699fc0();
  if ((iVar2 == 0) && ((*(int *)(param_1 + 0x34) == 0 || (*(int *)(param_1 + 0x74) != 0)))) {
    FUN_006919c0();
  }
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return uVar1;
}

