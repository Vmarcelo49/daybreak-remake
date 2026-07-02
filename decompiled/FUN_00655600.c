// Function: FUN_00655600
// Address:  0x00655600
// Source:   batch_decompile (mass dump)
// Hash:     8bc82e442a854f49


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00655600(char *param_1,char *param_2,char *param_3)

{
  undefined4 extraout_var;
  char local_114 [268];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  __splitpath(param_1,(char *)0x0,param_2,param_3,local_114);
  FUN_0066b870(param_3,local_114,extraout_var);
  return;
}

