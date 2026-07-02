// ============================================
// Address:  0x00655450
// Original: FUN_00655450
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00655450(int param_1,undefined4 param_2,undefined4 param_3)

{
  CHAR local_114 [264];
  undefined4 local_c;
  char *local_8;
  
  local_c = DAT_006b77f4;
  *(undefined4 *)(param_1 + 0x108) = param_2;
  *(undefined4 *)(param_1 + 0x10c) = param_3;
  GetModuleFileNameA((HMODULE)0x0,local_114,0x104);
  local_8 = _strrchr(local_114,0x2f);
  if (local_8 == (char *)0x0) {
    local_8 = _strrchr(local_114,0x5c);
  }
  local_8[1] = '\0';
  FUN_0066b860(param_1,local_114);
  return;
}

