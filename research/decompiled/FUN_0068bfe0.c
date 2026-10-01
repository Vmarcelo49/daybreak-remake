// Function: FUN_0068bfe0
// Address:  0x0068bfe0
// Source:   batch_decompile (mass dump)
// Hash:     995cd2f67d954b06


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

