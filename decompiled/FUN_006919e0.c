// Function: FUN_006919e0
// Address:  0x006919e0
// Source:   batch_decompile (mass dump)
// Hash:     c532774989ebd972


void * __thiscall FUN_006919e0(void *param_1,uint param_2)

{
  FUN_00691a10();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

