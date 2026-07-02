// ============================================
// Address:  0x00698c30
// Original: FUN_00698c30
// Status:   unreviewed
// ============================================


int FUN_00698c30(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_c;
  int *local_8;
  
  if (param_3 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    local_8 = (int *)0x0;
    iVar1 = FUN_006995a0(param_2,&local_8,param_4,&local_c);
    if (-1 < iVar1) {
      (**(code **)(*local_8 + 0x30))(local_8,local_c);
    }
    *param_3 = local_8;
  }
  return iVar1;
}

