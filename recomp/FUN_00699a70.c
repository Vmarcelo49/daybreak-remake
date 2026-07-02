// ============================================
// Address:  0x00699a70
// Original: FUN_00699a70
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00699a70(int param_1)

{
  FUN_006919a0();
  if (*(int *)(param_1 + 0x80) != 0) {
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x80),0xffffffff);
    CloseHandle(*(HANDLE *)(param_1 + 0x80));
    *(undefined4 *)(param_1 + 0x80) = 0;
  }
  return 0;
}

