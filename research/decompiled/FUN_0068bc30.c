// Function: FUN_0068bc30
// Address:  0x0068bc30
// Source:   batch_decompile (mass dump)
// Hash:     8254db407cf1c8c1


void __fastcall FUN_0068bc30(int param_1)

{
  ResetEvent(*(HANDLE *)(param_1 + 0xbc));
  SetEvent(*(HANDLE *)(param_1 + 0xc0));
  CloseHandle(*(HANDLE *)(param_1 + 0xc0));
  *(undefined4 *)(param_1 + 0xc4) = 2;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  return;
}

