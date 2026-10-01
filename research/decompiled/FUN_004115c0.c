// Function: FUN_004115c0
// Address:  0x004115c0
// Source:   batch_decompile (mass dump)
// Hash:     fe3e7cbb104f7c7c


void * __thiscall FUN_004115c0(void *param_1,uint param_2)

{
  FUN_00410ed0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

