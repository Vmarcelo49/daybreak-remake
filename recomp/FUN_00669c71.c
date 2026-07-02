// ============================================
// Address:  0x00669c71
// Original: FUN_00669c71
// Status:   unreviewed
// ============================================


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00669c71(void)

{
  undefined **local_14 [3];
  char *local_8;
  
  if ((_DAT_006d8478 & 1) == 0) {
    _DAT_006d8478 = _DAT_006d8478 | 1;
    local_8 = "bad allocation";
    exception::exception((exception *)&DAT_006d846c,&local_8);
    _DAT_006d846c = &PTR_FUN_006ab3c0;
    _atexit((_func_4879 *)&LAB_006a05df);
  }
  exception::exception((exception *)local_14,(exception *)&DAT_006d846c);
  local_14[0] = &PTR_FUN_006ab3c0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_14,&DAT_006b4154);
}

