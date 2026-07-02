// Function: FUN_004355d0
// Address:  0x004355d0
// Source:   batch_decompile (mass dump)
// Hash:     d781894bc09a4bb8


void * __thiscall FUN_004355d0(void *param_1,uint param_2)

{
  if ((param_2 & 2) == 0) {
    FUN_0042fe20();
    if ((param_2 & 1) != 0) {
      _free(param_1);
    }
  }
  else {
    _eh_vector_destructor_iterator_(param_1,0x970,*(int *)((int)param_1 + -4),FUN_0042fe20);
    if ((param_2 & 1) != 0) {
      _free((void *)((int)param_1 + -4));
    }
    param_1 = (void *)((int)param_1 + -4);
  }
  return param_1;
}

