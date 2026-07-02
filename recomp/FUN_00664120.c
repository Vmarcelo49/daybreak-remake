// ============================================
// Address:  0x00664120
// Original: FUN_00664120
// Status:   unreviewed
// ============================================


void FUN_00664120(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  undefined4 uVar1;
  int iVar2;
  void *pvStack_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f2b1;
  pvStack_10 = ExceptionList;
  ExceptionList = &pvStack_10;
  uVar1 = FUN_00664c20(1);
  local_8 = 0;
  iVar2 = FUN_00410cf0(0x11c,uVar1);
  local_8._0_1_ = 1;
  if (iVar2 != 0) {
    FUN_00664de0(param_1,param_2,param_3,param_4,param_5);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006641ce();
  return;
}

