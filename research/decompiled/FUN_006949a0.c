// Function: FUN_006949a0
// Address:  0x006949a0
// Source:   batch_decompile (mass dump)
// Hash:     bffcd4e2686d2871


int FUN_006949a0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined2 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                undefined4 param_9)

{
  int iVar1;
  int *local_8;
  
  iVar1 = FUN_006871d0(&DAT_006ad998,param_3);
  if (iVar1 == 0) {
    iVar1 = (**(code **)(*param_1 + 0x10))(param_1,0,param_4,&local_8);
    if (-1 < iVar1) {
      iVar1 = (**(code **)(*local_8 + 0x2c))
                        (local_8,param_1,param_2,param_5,param_6,param_7,param_8,param_9);
      (**(code **)(*local_8 + 8))(local_8);
    }
  }
  else {
    iVar1 = -0x7ffdffff;
  }
  return iVar1;
}

