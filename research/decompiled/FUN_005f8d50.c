// Function: FUN_005f8d50
// Address:  0x005f8d50
// Source:   batch_decompile (mass dump)
// Hash:     633c91f962f5fd1c


undefined4 __thiscall
FUN_005f8d50(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  void *pvVar1;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e6f1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x164);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_005f9090(param_1,*(undefined4 *)(*(int *)(param_1 + 0x40) + param_2 * 4),
                            param_2 * 0x9c + *(int *)(param_1 + 0x3c),
                            *(undefined4 *)(param_1 + 0x44),
                            param_2 * 0x38 + *(int *)(param_1 + 0x38),
                            param_2 * 0x1c + *(int *)(param_1 + 0x34),param_3,param_4,param_5);
  }
  ExceptionList = local_10;
  return local_20;
}

