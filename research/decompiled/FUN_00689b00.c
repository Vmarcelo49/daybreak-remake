// Function: FUN_00689b00
// Address:  0x00689b00
// Source:   batch_decompile (mass dump)
// Hash:     166c7447964b5b7e


int __thiscall FUN_00689b00(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  if (param_2[6] == 0) {
    iVar1 = 1;
  }
  else {
    iVar1 = (**(code **)(*param_2 + 0x2c))(param_1);
    if (-1 < iVar1) {
      (**(code **)(*(int *)param_2[6] + 8))(param_2[6]);
      param_2[6] = 0;
      iVar1 = 0;
    }
  }
  return iVar1;
}

