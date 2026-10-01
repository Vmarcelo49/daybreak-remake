// Function: FUN_00669390
// Address:  0x00669390
// Source:   batch_decompile (mass dump)
// Hash:     eb8671c8ba202f26


void * __thiscall FUN_00669390(void *param_1,uint param_2)

{
  FUN_00668b30();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

