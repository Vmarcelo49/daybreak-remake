// Function: FUN_0068e2e0
// Address:  0x0068e2e0
// Source:   batch_decompile (mass dump)
// Hash:     a7457b6d10e5ee42


void __fastcall FUN_0068e2e0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069f8ca;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006ad480;
  param_1[3] = &PTR_FUN_006ad444;
  param_1[4] = &PTR_LAB_006ad95c;
  local_8 = 6;
  FUN_0068fd50();
  FUN_0068f8c0();
  if (param_1[0x14] != 0) {
    if (param_1[0x14] != 0) {
      (**(code **)(*(int *)(param_1[0x14] + 8) + 0xc))(1);
    }
    param_1[0x14] = 0;
  }
  if (param_1[0x1e] != 0) {
    if ((int *)param_1[0x1e] != (int *)0x0) {
      (**(code **)(*(int *)param_1[0x1e] + 0xc))(1);
    }
    param_1[0x1e] = 0;
  }
  local_8._0_1_ = 5;
  FUN_0068dbb0();
  local_8._0_1_ = 4;
  FUN_0068dbb0();
  local_8._0_1_ = 3;
  FUN_0068dbb0();
  local_8._0_1_ = 2;
  FUN_00691d70();
  local_8._0_1_ = 1;
  FUN_00691d70();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00691d70();
  local_8 = 0xffffffff;
  FUN_00687ae0();
  ExceptionList = local_10;
  return;
}

