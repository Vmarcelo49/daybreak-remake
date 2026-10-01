// Function: FUN_00694e80
// Address:  0x00694e80
// Source:   batch_decompile (mass dump)
// Hash:     b01e8845a30dcc08


int FUN_00694e80(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int iVar1;
  int *local_8;
  
  iVar1 = FUN_00694b70(&local_8);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_8 + 0x38))(local_8,param_2,param_3,param_4,param_5);
    (**(code **)(*local_8 + 8))(local_8);
  }
  return iVar1;
}

