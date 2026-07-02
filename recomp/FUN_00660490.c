// ============================================
// Address:  0x00660490
// Original: FUN_00660490
// Status:   unreviewed
// ============================================


void __thiscall
FUN_00660490(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  undefined4 local_c;
  undefined *local_8;
  
  local_8 = &DAT_006d7668;
  local_c = (**(code **)*param_2)(&DAT_006d7668);
  if (param_2[1] != 0) {
    (**(code **)(*(int *)*param_1 + 0x14))(*param_1,param_2[1],0);
  }
  param_2[1] = 0;
  iVar1 = (**(code **)(*(int *)*param_1 + 0x38))
                    (*param_1,0,&local_c,1,param_3,0,param_2 + 1,param_4 | 0x20);
  if (iVar1 != 0) {
    param_2[1] = 0;
  }
  return;
}

