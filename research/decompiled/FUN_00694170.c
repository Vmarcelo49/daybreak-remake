// Function: FUN_00694170
// Address:  0x00694170
// Source:   batch_decompile (mass dump)
// Hash:     59c1bea43f5e0d4a


void __thiscall FUN_00694170(int *param_1,void *param_2)

{
  if (param_1[1] < *param_1) {
    FUN_006940b0(param_1[2]);
    param_1[2] = (int)param_2;
    param_1[1] = param_1[1] + 1;
  }
  else {
    _free(param_2);
  }
  return;
}

