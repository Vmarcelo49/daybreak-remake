// Function: FUN_00699020
// Address:  0x00699020
// Source:   batch_decompile (mass dump)
// Hash:     de78068f3c6a0def


void * __thiscall FUN_00699020(void *param_1,uint param_2)

{
  FUN_00698e30();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

