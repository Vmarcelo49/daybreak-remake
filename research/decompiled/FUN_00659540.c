// Function: FUN_00659540
// Address:  0x00659540
// Source:   batch_decompile (mass dump)
// Hash:     cfd620922fec164d


int __fastcall FUN_00659540(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = (*(int *)(param_1 + 8) - *(int *)(param_1 + 4)) / 0x50;
  }
  return local_c;
}

