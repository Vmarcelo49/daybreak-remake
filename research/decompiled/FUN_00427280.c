// Function: FUN_00427280
// Address:  0x00427280
// Source:   batch_decompile (mass dump)
// Hash:     02b1b8497c6ca6ec


void * __thiscall FUN_00427280(void *param_1,uint param_2)

{
  FUN_004234c0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

