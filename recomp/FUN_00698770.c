// ============================================
// Address:  0x00698770
// Original: FUN_00698770
// Status:   unreviewed
// ============================================


int FUN_00698770(undefined4 param_1,int *param_2,int param_3,undefined4 *param_4)

{
  int iVar1;
  int local_1c;
  int *local_18;
  undefined1 local_14 [8];
  undefined4 local_c;
  
  if (param_2 == (int *)0x0) {
    local_1c = -0x7fffbffd;
  }
  else if (param_3 == 0) {
    local_1c = -0x7fffbffd;
  }
  else if (param_4 == (undefined4 *)0x0) {
    local_1c = -0x7fffbffd;
  }
  else {
    if ((*(int *)(param_3 + 8) == 0) ||
       (iVar1 = FUN_00698fd0(*(undefined4 *)(param_3 + 8)), iVar1 == 0)) {
      FUN_00699ef0(param_3 + 8);
    }
    if (((param_2 == (int *)0x0) ||
        (iVar1 = (**(code **)(*param_2 + 0xc))(param_2,param_3,local_14), iVar1 < 0)) ||
       (iVar1 = FUN_00698fd0(local_c), iVar1 == 0)) {
      local_1c = FUN_00698630(&local_18);
      if (-1 < local_1c) {
        local_1c = (**(code **)(*local_18 + 0xc))(local_18,param_3,local_14);
        if ((local_1c < 0) || (iVar1 = FUN_00698fd0(local_c), iVar1 == 0)) {
          (**(code **)(*local_18 + 8))(local_18);
          if (-1 < local_1c) {
            local_1c = -0x7ffbfdf2;
          }
        }
        else {
          *param_4 = local_18;
          local_1c = 0;
        }
      }
    }
    else {
      (**(code **)(*param_2 + 4))(param_2);
      *param_4 = param_2;
      local_1c = 0;
    }
  }
  return local_1c;
}

