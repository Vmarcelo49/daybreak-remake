// Function: FUN_006950d0
// Address:  0x006950d0
// Source:   batch_decompile (mass dump)
// Hash:     ede2818752d42974


int FUN_006950d0(undefined4 param_1,double param_2)

{
  int iVar1;
  undefined4 local_8;
  
  if (param_2 == 0.0) {
    iVar1 = -0x7ff8ffa9;
  }
  else {
    iVar1 = FUN_00694b70();
    if (-1 < iVar1) {
      iVar1 = (**(code **)(*local_8 + 0x44))(local_8,param_2);
      (**(code **)(*local_8 + 8))(local_8);
    }
  }
  return iVar1;
}

