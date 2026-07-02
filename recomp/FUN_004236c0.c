// ============================================
// Address:  0x004236c0
// Original: FUN_004236c0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_004236c0(int param_1)

{
  undefined4 local_c;
  
  if ((*(int *)(param_1 + 0xadec) < 100) || (299 < *(int *)(param_1 + 0xadec))) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

