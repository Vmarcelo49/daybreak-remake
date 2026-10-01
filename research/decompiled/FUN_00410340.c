// Function: FUN_00410340
// Address:  0x00410340
// Source:   batch_decompile (mass dump)
// Hash:     ff84be5ff79aac36


void * __thiscall FUN_00410340(void *param_1,uint param_2)

{
  FID_conflict__logic_error();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

