// Function: FUN_004258e0
// Address:  0x004258e0
// Source:   batch_decompile (mass dump)
// Hash:     1f6692b64df77035


int __fastcall FUN_004258e0(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = (*(int *)(param_1 + 8) - *(int *)(param_1 + 4)) / 0xc;
  }
  return local_c;
}

