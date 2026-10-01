// Function: FUN_00659500
// Address:  0x00659500
// Source:   batch_decompile (mass dump)
// Hash:     8aab247787512acd


int __fastcall FUN_00659500(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = (*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) / 0x50;
  }
  return local_c;
}

