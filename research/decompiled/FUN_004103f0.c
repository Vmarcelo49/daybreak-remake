// Function: FUN_004103f0
// Address:  0x004103f0
// Source:   batch_decompile (mass dump)
// Hash:     2deb599d9e98f94e


void * __thiscall FUN_004103f0(void *param_1,uint param_2)

{
  FUN_004103d0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

