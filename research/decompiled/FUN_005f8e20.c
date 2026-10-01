// Function: FUN_005f8e20
// Address:  0x005f8e20
// Source:   batch_decompile (mass dump)
// Hash:     e0b5c353b19db527


void * __thiscall FUN_005f8e20(void *param_1,uint param_2)

{
  FUN_005f7f90();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

