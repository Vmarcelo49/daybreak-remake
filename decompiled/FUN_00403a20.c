// Function: FUN_00403a20
// Address:  0x00403a20
// Source:   batch_decompile (mass dump)
// Hash:     f40f79e6777bbfec


void * __thiscall FUN_00403a20(void *param_1,uint param_2)

{
  FUN_00402b60();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

