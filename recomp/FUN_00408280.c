// ============================================
// Address:  0x00408280
// Original: FUN_00408280
// Status:   unreviewed
// ============================================


void * __thiscall FUN_00408280(void *param_1,uint param_2)

{
  FUN_00406140();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

