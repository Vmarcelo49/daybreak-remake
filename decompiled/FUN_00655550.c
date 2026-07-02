// Function: FUN_00655550
// Address:  0x00655550
// Source:   batch_decompile (mass dump)
// Hash:     a3d82ec4f562acbb


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00655550(undefined4 param_1,undefined4 param_2)

{
  char local_114 [264];
  undefined4 local_c;
  char *local_8;
  
  local_c = DAT_006b77f4;
  FUN_0066b860(local_114,param_2,param_1);
  local_8 = _strrchr(local_114,0x2f);
  if (local_8 == (char *)0x0) {
    local_8 = _strrchr(local_114,0x5c);
  }
  local_8[1] = '\0';
  FUN_00655530();
  SetCurrentDirectoryA(local_114);
  return;
}

