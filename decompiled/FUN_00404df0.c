// Function: FUN_00404df0
// Address:  0x00404df0
// Source:   batch_decompile (mass dump)
// Hash:     76399f8973a16329


void * __thiscall FUN_00404df0(void *param_1,uint param_2)

{
  FUN_004041a0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

