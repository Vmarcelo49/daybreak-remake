// Function: FUN_00669b40
// Address:  0x00669b40
// Source:   batch_decompile (mass dump)
// Hash:     b588817030e48bd2


void * __thiscall FUN_00669b40(void *param_1,uint param_2)

{
  FUN_00669a80();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

