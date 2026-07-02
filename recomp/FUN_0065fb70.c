// ============================================
// Address:  0x0065fb70
// Original: FUN_0065fb70
// Status:   unreviewed
// ============================================


void __thiscall
FUN_0065fb70(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_c;
  undefined *local_8;
  
  if (*(char *)(param_1 + 0x1d) != '\0') {
    local_8 = &DAT_006d73d8;
    local_c = (**(code **)*param_2)(&DAT_006d73d8);
    if (param_2[1] != 0) {
      (**(code **)(*(int *)*param_1 + 0x18))(*param_1,param_2[1],0);
    }
    param_2[1] = 0;
    iVar1 = (**(code **)(*(int *)*param_1 + 0x20))
                      (*param_1,&local_c,1,param_3,0,param_2 + 1,param_4);
    if (iVar1 != 0) {
      param_2[1] = 0;
    }
  }
  return;
}

