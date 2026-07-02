// ============================================
// Address:  0x00693630
// Original: FUN_00693630
// Status:   unreviewed
// ============================================


void __fastcall FUN_00693630(undefined4 *param_1)

{
  void *pvVar1;
  void *local_8;
  
  local_8 = (void *)*param_1;
  while (local_8 != (void *)0x0) {
    pvVar1 = (void *)FUN_0068dc80();
    _free(local_8);
    local_8 = pvVar1;
  }
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  return;
}

