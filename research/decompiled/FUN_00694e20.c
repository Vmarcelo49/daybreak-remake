// Function: FUN_00694e20
// Address:  0x00694e20
// Source:   batch_decompile (mass dump)
// Hash:     03bcc7f428ab7058


int FUN_00694e20(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  int *local_8;
  
  iVar1 = FUN_00694b70(&local_8);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_8 + 0x34))(local_8,param_2,param_3,param_4,param_5,param_6);
    (**(code **)(*local_8 + 8))(local_8);
  }
  return iVar1;
}

