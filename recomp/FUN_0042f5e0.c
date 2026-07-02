// ============================================
// Address:  0x0042f5e0
// Original: FUN_0042f5e0
// Status:   unreviewed
// ============================================


undefined4 __thiscall
FUN_0042f5e0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  void *pvVar1;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e406;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x13c);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_0042f820(param_2 / 10,
                            *(undefined4 *)(*(int *)(param_1 + 0x38) + (param_2 / 10) * 4),
                            (param_2 / 10) * 0x38 + *(int *)(param_1 + 0x34),
                            param_2 * 0x1c + *(int *)(param_1 + 0x30),param_3,param_4,param_5);
  }
  ExceptionList = local_10;
  return local_20;
}

