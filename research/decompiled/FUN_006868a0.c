// Function: FUN_006868a0
// Address:  0x006868a0
// Source:   batch_decompile (mass dump)
// Hash:     08bb73be41b403ec


undefined4 __thiscall FUN_006868a0(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = FUN_00686f20(param_1,param_2);
  if ((iVar1 < 0) && (param_3 != (int *)0x0)) {
    *param_3 = iVar1;
  }
  return param_1;
}

