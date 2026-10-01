// Function: FUN_00433170
// Address:  0x00433170
// Source:   batch_decompile (mass dump)
// Hash:     04b11a98b857e272


void * __thiscall FUN_00433170(void *param_1,uint param_2)

{
  FUN_0040fbb0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

