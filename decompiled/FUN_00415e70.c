// Function: FUN_00415e70
// Address:  0x00415e70
// Source:   batch_decompile (mass dump)
// Hash:     2629a61571efbbb4


void * __thiscall FUN_00415e70(void *param_1,uint param_2)

{
  FUN_00414c40();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

