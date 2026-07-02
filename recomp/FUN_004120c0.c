// ============================================
// Address:  0x004120c0
// Original: FUN_004120c0
// Status:   unreviewed
// ============================================


void * __thiscall FUN_004120c0(void *param_1,uint param_2)

{
  FUN_004119f0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

