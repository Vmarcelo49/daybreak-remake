// Function: FUN_00694ee0
// Address:  0x00694ee0
// Source:   batch_decompile (mass dump)
// Hash:     ec2f7830253c5464


int FUN_00694ee0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *local_8;
  
  iVar1 = FUN_00694b70(&local_8);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_8 + 0x3c))(local_8,param_2,param_3);
    (**(code **)(*local_8 + 8))(local_8);
  }
  return iVar1;
}

