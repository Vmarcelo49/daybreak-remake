// ============================================
// Address:  0x006560c0
// Original: FUN_006560c0
// Status:   unreviewed
// ============================================


undefined4 * __thiscall FUN_006560c0(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_8;
  
  FUN_00425ac0(param_1);
  puVar1 = (undefined4 *)FUN_00656680(&local_8);
  *puVar1 = 0;
  iVar2 = FUN_00656c80(param_3,puVar1);
  if (iVar2 < 0) {
    FUN_0065a7f0(local_8);
    FUN_00654170(0);
  }
  else {
    *param_2 = local_8;
  }
  return param_2;
}

