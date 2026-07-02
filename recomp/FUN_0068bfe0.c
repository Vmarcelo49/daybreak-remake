// ============================================
// Address:  0x0068bfe0
// Original: FUN_0068bfe0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0068bfe0(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0xd0) == 0) || (*(int *)(param_1 + 0xd4) == 0)) {
    uVar1 = 0x80004005;
  }
  else {
    ResetEvent(*(HANDLE *)(param_1 + 0xd0));
    uVar1 = FUN_0068a320();
  }
  return uVar1;
}

