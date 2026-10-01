// Function: FUN_00694af0
// Address:  0x00694af0
// Source:   batch_decompile (mass dump)
// Hash:     309448d62c8cc7ce


undefined4 __thiscall FUN_00694af0(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 local_10;
  int local_c;
  int *local_8;
  
  *param_2 = 0;
  local_c = (**(code **)(**(int **)(param_1 + 0x18) + 0x18))
                      (*(undefined4 *)(param_1 + 0x18),&local_8);
  if (local_c < 0) {
    uVar1 = 0x80004001;
  }
  else {
    local_c = (**(code **)*local_8)(local_8,&LAB_006ad101_3,&local_10);
    (**(code **)(*local_8 + 8))(local_8);
    if (local_c < 0) {
      uVar1 = 0x80004001;
    }
    else {
      *param_2 = local_10;
      uVar1 = 0;
    }
  }
  return uVar1;
}

