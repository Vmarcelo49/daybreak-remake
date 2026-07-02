// Function: FUN_00686860
// Address:  0x00686860
// Source:   batch_decompile (mass dump)
// Hash:     4f5efc9ee8be24a0


undefined4 __thiscall FUN_00686860(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = FUN_00686f20(param_1,param_2);
  if ((iVar1 < 0) && (param_3 != (int *)0x0)) {
    *param_3 = iVar1;
  }
  return param_1;
}

