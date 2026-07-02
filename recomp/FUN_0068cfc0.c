// ============================================
// Address:  0x0068cfc0
// Original: FUN_0068cfc0
// Status:   unreviewed
// ============================================


void __thiscall FUN_0068cfc0(int *param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int *local_8;
  
  local_8 = param_1;
  while( true ) {
    if (*local_8 == 0) {
      return;
    }
    if (*local_8 == param_2) break;
    local_8 = (int *)FUN_0068dce0(*local_8);
  }
  piVar1 = (int *)FUN_0068dce0(param_2);
  *local_8 = *piVar1;
  puVar2 = (undefined4 *)FUN_0068dce0(param_2);
  *puVar2 = 0;
  param_1[1] = param_1[1] + -1;
  return;
}

