// ============================================
// Address:  0x00699020
// Original: FUN_00699020
// Status:   unreviewed
// ============================================


void * __thiscall FUN_00699020(void *param_1,uint param_2)

{
  FUN_00698e30();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

