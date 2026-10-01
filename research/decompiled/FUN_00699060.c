// Function: FUN_00699060
// Address:  0x00699060
// Source:   batch_decompile (mass dump)
// Hash:     62e959ab627b10dd


void * __thiscall FUN_00699060(void *param_1,uint param_2)

{
  FUN_00698430();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

