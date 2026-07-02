// ============================================
// Address:  0x00659500
// Original: FUN_00659500
// Status:   unreviewed
// ============================================


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

