// ============================================
// Address:  0x0068b9b0
// Original: FUN_0068b9b0
// Status:   unreviewed
// ============================================


int FUN_0068b9b0(undefined4 param_1,uint param_2,HANDLE param_3)

{
  BOOL BVar1;
  int local_c;
  
  if ((param_2 & 0xfffffffe) == 0) {
    if ((((param_2 & 1) == 0) || (param_3 == (HANDLE)0x0)) ||
       (BVar1 = ResetEvent(param_3), BVar1 != 0)) {
      if ((param_2 == 0) && (param_3 != (HANDLE)0x0)) {
        local_c = -0x7ff8ffa9;
      }
      else {
        if ((param_2 & 1) == 0) {
          local_c = FUN_0068bc90();
        }
        else if (param_3 == (HANDLE)0x0) {
          local_c = FUN_0068ba70();
        }
        else {
          local_c = FUN_0068baf0(param_3);
        }
        if (-1 < local_c) {
          local_c = 0;
        }
      }
    }
    else {
      local_c = FUN_00693210();
    }
  }
  else {
    local_c = -0x7ff8ffa9;
  }
  return local_c;
}

