// ============================================
// Address:  0x00418be0
// Original: FUN_00418be0
// Status:   unreviewed
// ============================================


void * __thiscall FUN_00418be0(void *param_1,uint param_2)

{
  FUN_00417b80();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

