// Function: FUN_00653b00
// Address:  0x00653b00
// Source:   batch_decompile (mass dump)
// Hash:     b5fa91b2794b4e36


void * __thiscall FUN_00653b00(void *param_1,uint param_2)

{
  FUN_00662950();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

