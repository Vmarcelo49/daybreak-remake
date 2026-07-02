// Function: FUN_00693260
// Address:  0x00693260
// Source:   batch_decompile (mass dump)
// Hash:     1a99892ba751b065


int * FUN_00693260(int *param_1,int *param_2)

{
  if (param_2 != (int *)0x0) {
    (**(code **)(*param_2 + 4))(param_2);
  }
  if (*param_1 != 0) {
    (**(code **)(*(int *)*param_1 + 8))(*param_1);
  }
  *param_1 = (int)param_2;
  return param_2;
}

