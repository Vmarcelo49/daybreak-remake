// Function: FUN_00418be0
// Address:  0x00418be0
// Source:   batch_decompile (mass dump)
// Hash:     6b0278f2ae6c2d77


void * __thiscall FUN_00418be0(void *param_1,uint param_2)

{
  FUN_00417b80();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

