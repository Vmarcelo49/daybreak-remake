// Function: FUN_00688be0
// Address:  0x00688be0
// Source:   batch_decompile (mass dump)
// Hash:     9030071c464b6098


undefined4 * __thiscall FUN_00688be0(undefined4 *param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  FUN_0068d8d0();
  *param_1 = &PTR_FUN_006ad284;
  param_1[1] = 0;
  param_1[2] = param_2;
  param_1[4] = 1;
  (**(code **)(*(int *)(param_1[2] + 0xc) + 4))(param_1[2] + 0xc);
  if (param_3 == 0) {
    uVar1 = (**(code **)(*(int *)param_1[2] + 0x10))();
    param_1[3] = uVar1;
  }
  else {
    param_1[1] = *(undefined4 *)(param_3 + 4);
    param_1[3] = *(undefined4 *)(param_3 + 0xc);
  }
  return param_1;
}

