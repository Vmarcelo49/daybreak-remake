// ============================================
// Address:  0x0068dd10
// Original: FUN_0068dd10
// Status:   unreviewed
// ============================================


void __thiscall FUN_0068dd10(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_0068dce0(param_2);
  *puVar1 = *param_1;
  *param_1 = param_2;
  param_1[1] = param_1[1] + 1;
  return;
}

