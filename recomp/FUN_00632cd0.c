// ============================================
// Address:  0x00632cd0
// Original: FUN_00632cd0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00632cd0(int *param_1)

{
  void *pvVar1;
  int iVar2;
  int local_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e72b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*param_1 != 0) {
    ExceptionList = &local_10;
    if (*param_1 != 0) {
      ExceptionList = &local_10;
      FUN_00402010(1);
    }
    *param_1 = 0;
  }
  pvVar1 = operator_new(0x9c);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_2c = 0;
  }
  else {
    local_2c = FUN_0064d7a0();
  }
  local_8 = 0xffffffff;
  *param_1 = local_2c;
  FUN_0064d940("data/camera/01.x");
  iVar2 = FUN_0064e6c0("Box01");
  param_1[1] = iVar2;
  iVar2 = FUN_0064e6c0("Box02");
  param_1[2] = iVar2;
  ExceptionList = local_10;
  return;
}

