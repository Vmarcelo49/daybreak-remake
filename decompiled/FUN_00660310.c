// Function: FUN_00660310
// Address:  0x00660310
// Source:   batch_decompile (mass dump)
// Hash:     c8f4027bc60970ad


void __thiscall FUN_00660310(int *param_1,int param_2)

{
  if (*param_1 != 0) {
    (**(code **)(*(int *)*param_1 + 0x14))(*param_1,param_1[param_2 + 2],0x80000000);
    (**(code **)(*(int *)*param_1 + 0x60))(*param_1,param_1[param_2 + 2],0,0,0);
    param_1[param_2 + 10] = -1;
    FUN_0065d670();
    if (param_1[0x19] != 0) {
      (**(code **)(*(int *)param_1[0x19] + 0x10))(param_2);
    }
    FUN_0065d6a0();
  }
  return;
}

