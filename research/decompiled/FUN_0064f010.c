// Function: FUN_0064f010
// Address:  0x0064f010
// Source:   batch_decompile (mass dump)
// Hash:     542b13136c46aa21


int __fastcall FUN_0064f010(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = *(int *)(param_1 + 8) - *(int *)(param_1 + 4) >> 2;
  }
  return local_c;
}

