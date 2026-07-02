// Function: FUN_0065aa30
// Address:  0x0065aa30
// Source:   batch_decompile (mass dump)
// Hash:     0e37595a8dad4078


int __fastcall FUN_0065aa30(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4) >> 2;
  }
  return local_c;
}

