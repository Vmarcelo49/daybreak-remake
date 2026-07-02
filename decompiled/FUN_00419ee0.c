// Function: FUN_00419ee0
// Address:  0x00419ee0
// Source:   batch_decompile (mass dump)
// Hash:     58a3f30ae2042c51


void * __thiscall FUN_00419ee0(void *param_1,uint param_2)

{
  FUN_00419470();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

