// ============================================
// Address:  0x005f7b80
// Original: FUN_005f7b80
// Status:   unreviewed
// ============================================


void * __thiscall FUN_005f7b80(void *param_1,uint param_2)

{
  FUN_005f7b60();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

