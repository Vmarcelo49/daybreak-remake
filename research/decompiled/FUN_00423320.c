// Function: FUN_00423320
// Address:  0x00423320
// Source:   batch_decompile (mass dump)
// Hash:     9290f62027a09db8


void * __thiscall FUN_00423320(void *param_1,uint param_2)

{
  FUN_0041da70();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

