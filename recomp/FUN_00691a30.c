// ============================================
// Address:  0x00691a30
// Original: FUN_00691a30
// Status:   unreviewed
// ============================================


void * __thiscall FUN_00691a30(void *param_1,uint param_2)

{
  FUN_00690730();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

