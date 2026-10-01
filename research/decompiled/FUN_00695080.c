// Function: FUN_00695080
// Address:  0x00695080
// Source:   batch_decompile (mass dump)
// Hash:     a83d959aff28b73e


int FUN_00695080(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *local_8;
  
  iVar1 = FUN_00694b70(&local_8);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_8 + 0x48))(local_8,param_2);
    (**(code **)(*local_8 + 8))(local_8);
  }
  return iVar1;
}

