// Function: FUN_004039f0
// Address:  0x004039f0
// Source:   batch_decompile (mass dump)
// Hash:     ebc8a5b2b6acecf8


void * __thiscall FUN_004039f0(void *param_1,uint param_2)

{
  FUN_004039d0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

