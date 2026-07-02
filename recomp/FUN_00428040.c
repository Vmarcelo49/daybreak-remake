// ============================================
// Address:  0x00428040
// Original: FUN_00428040
// Status:   unreviewed
// ============================================


void FUN_00428040(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00410cf0(0xc,param_1);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_2;
    puVar1[1] = param_2[1];
    puVar1[2] = param_2[2];
  }
  return;
}

