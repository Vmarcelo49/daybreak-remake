// ============================================
// Address:  0x0064ddd0
// Original: FUN_0064ddd0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_0064ddd0(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int local_28;
  int local_24;
  CHAR local_20 [16];
  undefined4 local_10;
  size_t local_c;
  int local_8;
  
  local_10 = DAT_006b77f4;
  local_8 = 0;
  if (*param_3 != 0) {
    for (local_24 = 0; local_24 < 2; local_24 = local_24 + 1) {
      wsprintfA(local_20,"%s%02d",param_2,local_24);
      local_c = _strlen(local_20);
      iVar1 = _strncmp(local_20,(char *)*param_3,local_c);
      if (iVar1 == 0) {
        local_8 = local_24;
        break;
      }
    }
  }
  for (local_28 = 0; local_28 < 2; local_28 = local_28 + 1) {
    if (local_28 == local_8) {
      (**(code **)(**(int **)(param_1 + 0xc + local_28 * 4) + 0x1c))
                (*(undefined4 *)(param_1 + 0xc + local_28 * 4),*param_3,param_3 + 1,0,0,0);
    }
    else {
      (**(code **)(**(int **)(param_1 + 0xc + local_28 * 4) + 0x1c))
                (*(undefined4 *)(param_1 + 0xc + local_28 * 4),*param_3,0,0,0,0);
    }
  }
  if (param_3[0x12] != 0) {
    FUN_0064ddd0(param_2,param_3[0x12]);
  }
  if (param_3[0x13] != 0) {
    FUN_0064ddd0(param_2,param_3[0x13]);
  }
  return;
}

