// Function: FUN_00405220
// Address:  0x00405220
// Source:   batch_decompile (mass dump)
// Hash:     43bbfcaa86fb38b6


void * __thiscall FUN_00405220(void *param_1,uint param_2)

{
  FUN_00404f90();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

