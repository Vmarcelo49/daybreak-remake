// Function: FUN_0068cd10
// Address:  0x0068cd10
// Source:   batch_decompile (mass dump)
// Hash:     6b7f2083ddfcbd45


void __fastcall FUN_0068cd10(int param_1)

{
  if (*(int *)(param_1 + 0x34) != 0) {
    ReleaseSemaphore(*(HANDLE *)(param_1 + 0x30),*(LONG *)(param_1 + 0x34),(LPLONG)0x0);
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  return;
}

