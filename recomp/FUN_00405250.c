// ============================================
// Address:  0x00405250
// Original: FUN_00405250
// Status:   unreviewed
// ============================================


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

