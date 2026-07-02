// Function: FUN_005f7700
// Address:  0x005f7700
// Source:   batch_decompile (mass dump)
// Hash:     252ecb5fe28b99e2


void * __thiscall FUN_005f7700(void *param_1,uint param_2)

{
  FUN_004366f0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

