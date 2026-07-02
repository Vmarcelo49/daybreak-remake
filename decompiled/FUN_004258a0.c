// Function: FUN_004258a0
// Address:  0x004258a0
// Source:   batch_decompile (mass dump)
// Hash:     cc416cd2e8fb4afb


int __fastcall FUN_004258a0(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = (*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) / 0xc;
  }
  return local_c;
}

