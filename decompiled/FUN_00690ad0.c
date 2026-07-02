// Function: FUN_00690ad0
// Address:  0x00690ad0
// Source:   batch_decompile (mass dump)
// Hash:     8e7acba45929c0e1


void __fastcall FUN_00690ad0(int param_1)

{
  if (*(int *)(param_1 + 0xf0) < 1) {
    Sleep(0);
  }
  else {
    Sleep(*(int *)(param_1 + 0xf0) / 10000);
  }
  return;
}

