// ============================================
// Address:  0x006882b0
// Original: FUN_006882b0
// Status:   unreviewed
// ============================================


undefined4 FUN_006882b0(int param_1,undefined4 param_2,void *param_3)

{
  int iVar1;
  void *pvVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f4e9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(*(undefined4 *)(param_1 + 0x2c));
  local_8 = 0;
  *(undefined4 *)(param_1 + 0x34) = param_2;
  if (*(int *)(param_1 + 0x34) == 0) {
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  else {
    iVar1 = (**(code **)**(undefined4 **)(param_1 + 0x34))
                      (*(undefined4 *)(param_1 + 0x34),&DAT_006acfb4,param_1 + 0x38);
    if (-1 < iVar1) {
      (**(code **)(**(int **)(param_1 + 0x38) + 8))(*(undefined4 *)(param_1 + 0x38));
    }
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    _free(*(void **)(param_1 + 0x30));
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  if (param_3 != (void *)0x0) {
    iVar1 = FUN_006925d0(param_3);
    pvVar2 = operator_new((iVar1 + 1) * 2);
    *(void **)(param_1 + 0x30) = pvVar2;
    if (*(int *)(param_1 + 0x30) != 0) {
      _memcpy(*(void **)(param_1 + 0x30),param_3,(iVar1 + 1) * 2);
    }
  }
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

