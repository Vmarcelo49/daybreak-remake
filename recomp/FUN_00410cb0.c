// ============================================
// Address:  0x00410cb0
// Original: FUN_00410cb0
// Status:   unreviewed
// ============================================


void FUN_00410cb0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)FUN_00410cf0(8,param_1);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = param_2[1];
    *puVar2 = *param_2;
    puVar2[1] = uVar1;
  }
  return;
}

