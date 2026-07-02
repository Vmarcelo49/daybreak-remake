// ============================================
// Address:  0x00669c3d
// Original: FUN_00669c3d
// Status:   unreviewed
// ============================================


void * __thiscall FUN_00669c3d(void *param_1,byte param_2)

{
  FUN_00669c32();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

