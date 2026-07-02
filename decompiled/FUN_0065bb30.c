// Function: FUN_0065bb30
// Address:  0x0065bb30
// Source:   batch_decompile (mass dump)
// Hash:     9b018010fefa9618


void __fastcall FUN_0065bb30(undefined4 *param_1)

{
  while (*(char *)(param_1 + 0x4d3) != '\0') {
    if (*(char *)((int)param_1 + 0x134d) != '\0') {
      FUN_0065bb70();
    }
    WaitForSingleObject((HANDLE)*param_1,0x14);
  }
  return;
}

