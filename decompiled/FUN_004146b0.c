// Function: FUN_004146b0
// Address:  0x004146b0
// Source:   batch_decompile (mass dump)
// Hash:     52d16d31237e0eff


void * __thiscall FUN_004146b0(void *param_1,uint param_2)

{
  FUN_004129c0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

