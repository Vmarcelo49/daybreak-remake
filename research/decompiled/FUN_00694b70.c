// Function: FUN_00694b70
// Address:  0x00694b70
// Source:   batch_decompile (mass dump)
// Hash:     de4ff2a1e9a557cb


undefined4 __thiscall FUN_00694b70(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  int *local_8;
  
  *param_2 = 0;
  iVar1 = (**(code **)(**(int **)(param_1 + 0x18) + 0x18))(*(undefined4 *)(param_1 + 0x18),&local_8)
  ;
  if (iVar1 < 0) {
    uVar2 = 0x80004001;
  }
  else {
    iVar1 = (**(code **)*local_8)(local_8,&DAT_006acfe4,&local_c);
    (**(code **)(*local_8 + 8))(local_8);
    if (iVar1 < 0) {
      uVar2 = 0x80004001;
    }
    else {
      *param_2 = local_c;
      uVar2 = 0;
    }
  }
  return uVar2;
}

