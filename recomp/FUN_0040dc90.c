// ============================================
// Address:  0x0040dc90
// Original: FUN_0040dc90
// Status:   unreviewed
// ============================================


void * __thiscall FUN_0040dc90(void *param_1,uint param_2)

{
  FUN_0040dcc0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

