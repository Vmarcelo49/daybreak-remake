// ============================================
// Address:  0x00403e80
// Original: FUN_00403e80
// Status:   unreviewed
// ============================================


void * __thiscall FUN_00403e80(void *param_1,uint param_2)

{
  FUN_00403d10();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

