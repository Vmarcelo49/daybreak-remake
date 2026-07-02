// Function: FUN_0068fc20
// Address:  0x0068fc20
// Source:   batch_decompile (mass dump)
// Hash:     2ea7a21a74f9e599


void __fastcall FUN_0068fc20(int param_1)

{
  if (*(int *)(param_1 + 0xc0) != 0) {
    timeKillEvent(*(UINT *)(param_1 + 0xc0));
    *(undefined4 *)(param_1 + 0xc0) = 0;
  }
  return;
}

