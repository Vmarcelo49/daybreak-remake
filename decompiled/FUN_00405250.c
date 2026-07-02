// Function: FUN_00405250
// Address:  0x00405250
// Source:   batch_decompile (mass dump)
// Hash:     c4affc6dcf519c80


undefined1 __fastcall FUN_00405250(int param_1)

{
  undefined1 local_c;
  
  if ((*(int *)(param_1 + 100) == 1) && (*(int *)(param_1 + 0x60) == 0)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

