// ============================================
// Address:  0x00419b00
// Original: FUN_00419b00
// Status:   unreviewed
// ============================================


undefined4 FUN_00419b00(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined4 local_34;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069df86;
  local_10 = ExceptionList;
  if ((param_1 < 1) || ((int)DAT_006cfdd0 <= DAT_006cfdcc + 1)) {
    uVar1 = 0;
  }
  else if ((&DAT_006cfdd1)[param_1] == '\0') {
    ExceptionList = &local_10;
    FUN_0065d670();
    (&DAT_006cfdd1)[param_1] = 1;
    (&DAT_006cfdf1)[param_1] = 0;
    local_14 = 0;
    for (local_18 = 1; local_18 < 8; local_18 = local_18 + 1) {
      if ((&DAT_006cfdd1)[local_18] != '\0') {
        local_14 = local_14 + 1;
      }
    }
    DAT_006cfdcc = local_14;
    if (*(int *)(DAT_006cfa24 + param_1 * 4) != 0) {
      if (*(int *)(DAT_006cfa24 + param_1 * 4) != 0) {
        FUN_0040dce0(1);
      }
      *(undefined4 *)(DAT_006cfa24 + param_1 * 4) = 0;
    }
    pvVar2 = operator_new(0x180);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_34 = 0;
    }
    else {
      local_34 = FUN_0040dab0();
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(DAT_006cfa24 + param_1 * 4) = local_34;
    FUN_0040da90();
    FUN_0064aed0(0);
    _memset(&DAT_006cfdfc,0,0x20);
    FUN_0065d6a0();
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  ExceptionList = local_10;
  return uVar1;
}

