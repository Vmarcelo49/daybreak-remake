// Function: FUN_00693370
// Address:  0x00693370
// Source:   batch_decompile (mass dump)
// Hash:     be326f50f2ba7e41


void __fastcall FUN_00693370(int param_1)

{
  HANDLE hHandle;
  
  hHandle = (HANDLE)InterlockedExchange((LONG *)(param_1 + 0x14),0);
  if (hHandle != (HANDLE)0x0) {
    WaitForSingleObject(hHandle,0xffffffff);
    CloseHandle(hHandle);
  }
  return;
}

