// ============================================
// Address:  0x0042e950
// Original: FUN_0042e950
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0042e950(int param_1)

{
  undefined4 local_c;
  
  if (((*(int *)(param_1 + 0xadec) < 300) || (0x17b < *(int *)(param_1 + 0xadec))) &&
     (*(int *)(param_1 + 0xadec) < 400)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

