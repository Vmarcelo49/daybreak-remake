// ============================================
// Address:  0x00695af0
// Original: FUN_00695af0
// Status:   unreviewed
// ============================================


undefined4 FUN_00695af0(int param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fca9;
  local_10 = ExceptionList;
  if (param_2 == (undefined8 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x34));
    local_8 = 0;
    uVar2 = FUN_00697fc0();
    *param_2 = uVar2;
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0;
  }
  ExceptionList = local_10;
  return uVar1;
}

