// Function: FUN_0041b880
// Address:  0x0041b880
// Source:   batch_decompile (mass dump)
// Hash:     9b72eb4bb9ef590b


void * __thiscall FUN_0041b880(void *param_1,uint param_2)

{
  FUN_0041b120();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

