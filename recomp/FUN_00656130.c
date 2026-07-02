// ============================================
// Address:  0x00656130
// Original: FUN_00656130
// Status:   unreviewed
// ============================================


undefined4 * __thiscall
FUN_00656130(undefined4 param_1,undefined4 *param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 *puVar1;
  undefined4 local_8;
  
  FUN_00425ac0(param_1);
  puVar1 = (undefined4 *)FUN_00656680(&local_8);
  *puVar1 = param_3;
  if ((param_4 != 0) && (param_5 != 0)) {
    FUN_00656380(local_8,param_4,param_5);
  }
  *param_2 = local_8;
  return param_2;
}

