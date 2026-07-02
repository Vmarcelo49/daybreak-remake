// Function: FUN_00403c30
// Address:  0x00403c30
// Source:   batch_decompile (mass dump)
// Hash:     133df94c96f51434


void * __thiscall FUN_00403c30(void *param_1,uint param_2)

{
  FUN_00403b00();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

