// Function: FUN_0068fe20
// Address:  0x0068fe20
// Source:   batch_decompile (mass dump)
// Hash:     6fcc9c6d7ed3ced5


void __thiscall FUN_0068fe20(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  int *local_8;
  
  iVar1 = (**(code **)*param_2)(param_2,&DAT_006acfb4,&local_8,param_1);
  if (-1 < iVar1) {
    (**(code **)(*local_8 + 0xc))(local_8,0x19,param_3,0);
    (**(code **)(*local_8 + 8))(local_8);
  }
  FUN_006883f0(0x19,param_3,0);
  return;
}

