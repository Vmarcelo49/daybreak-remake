// ============================================
// Address:  0x0065aa30
// Original: FUN_0065aa30
// Status:   unreviewed
// ============================================


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

