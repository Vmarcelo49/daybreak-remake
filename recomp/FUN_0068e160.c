// ============================================
// Address:  0x0068e160
// Original: FUN_0068e160
// Status:   unreviewed
// ============================================


undefined4 * __thiscall
FUN_0068e160(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f870;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00687920(param_3,param_4,param_1 + 0x1f,param_2);
  local_8 = 0;
  *param_1 = &PTR_FUN_006ad480;
  param_1[3] = &PTR_FUN_006ad444;
  param_1[4] = &PTR_LAB_006ad95c;
  param_1[0x14] = 0;
  FUN_00691d40(0);
  local_8._0_1_ = 1;
  FUN_00691d40(1);
  local_8._0_1_ = 2;
  FUN_00691d40(1);
  local_8._0_1_ = 3;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  FUN_0068db90();
  local_8._0_1_ = 4;
  FUN_0068db90();
  local_8._0_1_ = 5;
  param_1[0x2b] = 0;
  param_1[0x2c] = 1;
  param_1[0x2d] = 0;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  param_1[0x30] = 0;
  FUN_0068db90();
  local_8 = CONCAT31(local_8._1_3_,6);
  FUN_00691bf0();
  ExceptionList = local_10;
  return param_1;
}

