// Function: FUN_00699a70
// Address:  0x00699a70
// Source:   batch_decompile (mass dump)
// Hash:     ab607f0edda5311b


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

