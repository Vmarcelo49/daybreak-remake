// ============================================
// Address:  0x00660520
// Original: FUN_00660520
// Status:   unreviewed
// ============================================


void __thiscall
FUN_00660520(undefined4 *param_1,int param_2,undefined4 *param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  undefined4 local_c;
  undefined *local_8;
  
  if (param_2 == 0) {
    FUN_00660490(param_3,param_4,param_5);
  }
  else if (param_1[param_2 + 10] != 0) {
    local_8 = &DAT_006d7768;
    local_c = (**(code **)*param_3)(&DAT_006d7768);
    if (param_3[1] != 0) {
      (**(code **)(*(int *)*param_1 + 0x14))(*param_1,param_3[1],0);
    }
    param_3[1] = 0;
    iVar1 = (**(code **)(*(int *)*param_1 + 0x38))
                      (*param_1,param_1[param_2 + 2],&local_c,1,param_4,0,param_3 + 1,param_5 | 0x20
                      );
    if (iVar1 != 0) {
      param_3[1] = 0;
    }
  }
  return;
}

