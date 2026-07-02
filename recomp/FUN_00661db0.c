// ============================================
// Address:  0x00661db0
// Original: FUN_00661db0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00661db0(char *param_1,char *param_2)

{
  undefined4 local_118;
  undefined1 local_114 [264];
  undefined4 local_c;
  size_t local_8;
  
  local_c = DAT_006b77f4;
  local_118 = param_1;
  if (*param_1 == '\0') {
    FUN_00669510(param_2);
  }
  else {
    local_8 = _strlen(param_2);
    FUN_0066b860(local_114,param_2);
    local_114[local_8 - 3] = 99;
    local_114[local_8 - 2] = 0x6e;
    local_114[local_8 - 1] = 0x76;
    FUN_00669540(local_114);
  }
  return;
}

