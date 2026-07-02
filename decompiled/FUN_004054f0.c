// Function: FUN_004054f0
// Address:  0x004054f0
// Source:   batch_decompile (mass dump)
// Hash:     9e42a0c5e7a68c82


void * __thiscall FUN_004054f0(void *param_1,uint param_2)

{
  FUN_00405370();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

