// ============================================
// Address:  0x0065b0d0
// Original: FUN_0065b0d0
// Status:   unreviewed
// ============================================


undefined4 * FUN_0065b0d0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  void *pvVar3;
  int local_30;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f030;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00425ac0();
  piVar2 = (int *)FUN_0065a730(&local_14);
  pvVar3 = operator_new(0x1c);
  local_8 = 0;
  if (pvVar3 == (void *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_0065a3c0();
  }
  local_8 = 0xffffffff;
  *piVar2 = local_30;
  cVar1 = FUN_00661db0(param_2,*piVar2);
  if (cVar1 == '\0') {
    if (*piVar2 != 0) {
      FUN_0065a3f0(1);
    }
    FUN_0065a7f0(local_14);
    FUN_00654170(0);
  }
  else {
    *param_1 = local_14;
  }
  ExceptionList = local_10;
  return param_1;
}

